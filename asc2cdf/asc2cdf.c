/*
-------------------------------------------------------------------------
OBJECT NAME:	asc2cdf.c

FULL NAME:	ASCII to Nimbus-netCDF Low Rate

ENTRY POINTS:	main()

STATIC FNS:	ProcessArgv()
		WriteMissingData()

DESCRIPTION:	Translate ASCII file to Nimbus Low Rate netCDF file

COPYRIGHT:	University Corporation for Atmospheric Research, 1996-2007
-------------------------------------------------------------------------
*/

#include "define.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

char	buffer[BUFFSIZE];
char    histo_vars[MAX_VARS][256] = {"\0"};
int     vars_columns[MAX_VARS];

int	ncid;
int	status;
int	baseTimeID, timeOffsetID, timeVarID, varid[MAX_VARS], nVariables;
time_t	BaseTime = 0;
float	scale[MAX_VARS], offset[MAX_VARS], missingVals[MAX_VARS];
bool	getRec = true;
bool	notLastRec = true;

int	hour, minute, second, firstSecond, prevSecond = -1;
double	currSecond;
int	subsec;
int	startHour, startMinute, startSecond;
float	dataValue;

char FlightDate[50];

static FILE	*inFP;
static size_t	nRecords;
static char	*globalAttrFile = 0;

/* Command line option flags.
 */
InputFileType	fileType = PLAIN_FILE;
bool	secondsSinceMidnight = false, Colonless = false;
bool    verbose = false, histogram = false;
int	SkipNlines = 1;

int		BaseDataRate = 1, dataRate = 1;
const int	rateOne = 1;

const char	*noTitle = "No Title";
const char	*noUnits = "Unk";

void addGlobalAttrs(const char *p), WriteBaseTime();
void handle_error(const int);

static int ProcessArgv(int argc, char **argv);
static size_t ProcessTime(char *p);
static void WriteMissingData(int, int);


/* -------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
  int	i, j, k, hz;
  int	count;
  char	*p;
  size_t index[3];
  size_t rec;

  putenv((char *)"TZ=UTC");	// All time calcs in UTC.
  FlightDate[0] = 0;

  i = ProcessArgv(argc, argv);

  if ((argc - i) < 2)
    {
    fprintf(stderr, "Usage: asc2cdf [-b time_t] [-a] [-l] [-c] [-m] [-r n] [-s n] ascii_file output.nc\n");
    exit(1);
    }

  if ((inFP = fopen(argv[i], "r")) == NULL)
    {
    fprintf(stderr, "Can't open input file %s.\n", argv[i]);
    exit(1);
    }


  if (nc_create(argv[i+1], NC_CLOBBER, &ncid) != NC_NOERR)
    {
    fprintf(stderr, "Can't destroy/create output file %s.\n", argv[i+1]);
    exit(1);
    }


  switch (fileType)
    {
    case PLAIN_FILE:
      CreatePlainNetCDF(inFP);
      SetPlainBaseTime();
      break;

    case NASA_AMES:
      CreateNASAamesNetCDF(inFP);
      break;

    case ICARTT:
      CreateICARTTnetCDF(inFP);
      break;

    case NASA_LANGLEY:
      CreateNASAlangNetCDF(inFP);
      break;

    case BADC_CSV:
      CreateBADCnetCDF(inFP);
      break;
    }

  addGlobalAttrs(globalAttrFile);
  status = nc_enddef(ncid);
  if (status != NC_NOERR) handle_error(status);

  WriteBaseTime();

  printf("Averaging Period = %d, Data Rate = %dHz\n", BaseDataRate, dataRate);


  /* Start uploading data.
   */
  rewind(inFP);

  while (SkipNlines--)
    fgets(buffer, BUFFSIZE, inFP);


  for (nRecords = 0; notLastRec; )
    {
    if (getRec)
      {
      if (fgets(buffer, BUFFSIZE, inFP) == NULL) 
      {
        notLastRec = false;
	break;
      }
      // I am not sure why this test is here. I can imagine good data in seconds since midnight with 1
      // column of time and one of data, so "1,23". It would be rare, but is it bad data?? Is this there
      // to catch something else??
      if (strlen(buffer) < 5)
        continue;

      p = strtok(buffer, ", \t");	// Parse the first value (Time) out of the buffer

      } 
    else 
      {
	getRec=true;
      }


    if (fileType == NASA_LANGLEY)	/* Skip Julian day column */
      p = strtok(NULL, ", \t");

    if (fileType == BADC_CSV)   {       /* "end date" means no more data */
      if (strncmp(p,"end",3) == 0) {
	// Break out of hz loop
	notLastRec = false;
	continue;
      }
    }

    rec = ProcessTime(p);
    // Ignore duplicate timestamp
    if (int(rec) == -1) continue;
    

//    dataValue = (float)(nRecords * BaseDataRate);
//    nc_put_var1_float(ncid, timeVarID, &nRecords, &dataValue);
//    nc_put_var1_float(ncid, timeOffsetID, &nRecords, &dataValue);

    //If subseconds are given in the time column, offset here.-JAG
    if (verbose) 
	printf("subsec: %d ; dataRate: %d\n",subsec,dataRate);
    for (hz = subsec; hz < dataRate; ++hz)
      {
      // If histogram data, zeroth data bin must be zero for legacy
      // reasons.
      if (histogram || (strcmp(histo_vars[i],"\0")!=0)) {
	dataValue = 0;
        index[0] = rec; index[1] = hz; index[2] = 0;
        status = nc_put_var1_float(ncid, varid[1], index, &dataValue);
        if (status != NC_NOERR) handle_error(status);
      }
      j=0; // index for histograms
      for (i = 0; i < nVariables; ++i)
      {
        if ((p = strtok(NULL, ", \t\n\r")) == NULL)
          fprintf(stderr, "Not enough data points in row # %zu, check your formating;\n   are there spaces in a variable name on the title line?\n", nRecords);

        if (p)
          dataValue = atof(p);
        else
          dataValue = MISSING_VALUE;

        if (fileType != PLAIN_FILE)
          {
          if (dataValue == missingVals[i] || dataValue == missingVals[vars_columns[i]])
            dataValue = MISSING_VALUE;
          else
            dataValue = dataValue * scale[i] + offset[i];
          }

        if (histogram) {
          index[0] = rec; index[1] = hz; index[2] = i+1;
	  if (verbose)
	      printf("A: Writing data point %f to variable %d:%d [%lu,%d,%d] \n",dataValue,varid[1],i,rec,hz,i+1);
          status = nc_put_var1_float(ncid, varid[1], index, &dataValue);
          if (status != NC_NOERR) handle_error(status);
        } 
	else if (strlen(histo_vars[vars_columns[i]])>0) 
	{
          index[0] = rec; index[1] = hz; index[2] = j;
	  if (verbose)
	    printf("B: Writing data point %f to variable %d:%d [%lu,%d,%d] \n",dataValue,varid[vars_columns[i]],i,rec,hz,j);
	  // Use variable/column mapping to figure out which variable to put this value in.
          status = nc_put_var1_float(ncid, varid[vars_columns[i]], index, &dataValue);
          if (status != NC_NOERR) handle_error(status);
	  // Count number of columns in this histogram
	  count = 0;
 	  for (k=0;k<nVariables;k++) {
 	    if (vars_columns[k]==vars_columns[i]) count++;
 	  }
	  j++;
 	  if (j >= count) j=0;
        }
        else
        {
          index[0] = rec; index[1] = hz;
	  if (verbose)
	    printf("C: Writing data point %f to variable %d:%d [%lu,%d] \n",dataValue,varid[i],i,rec,hz);
          status = nc_put_var1_float(ncid, varid[i], index, &dataValue);
          if (status != NC_NOERR) handle_error(status);
        }
      }

      // If haven't read all the sub-dataRate data, keep looping until reach 
      // next time interval. Compare on current time to avoid merging data
      // from different seconds into a single second record. This additional
      // fgets will cause us to loose a record when time passes a multiple 
      // of data rate. Set a flag so we don't repeat fgets at top of loop.
      if (hz != dataRate-1) {
	getRec = false;
        if (fgets(buffer, BUFFSIZE, inFP) == NULL) 
        {
          notLastRec = false;
	  break;
        }
        // I am not sure why this test is here. I can imagine good data in seconds since midnight with 1
        // column of time and one of data, so "1,23". It would be rare, but is it bad data?? Is this there
        // to catch something else??
        if (strlen(buffer) < 5)
          continue;
        p = strtok(buffer, ", \t");
        if (fileType == BADC_CSV)	{	/* "end date" means no more data */
          if (strncmp(p,"end",3) == 0) {
	    // Break out of hz loop
	    notLastRec = false;
	    break;
	  }
        }

	if (atoi(p) != int(currSecond)) // found a new second, so break out of hz loop
	  break;

        // look for data gaps and handle appropriately
        subsec = int(atof(p)*dataRate-currSecond*dataRate);
        if (subsec != hz+1) { // found a sub-second data gap for data with rates > 1sps
	  hz= subsec-1;
        }

      } else {
	getRec = true;
      }

      
      if (fileType == NASA_LANGLEY)     /* Skip Julian day      */
        p = strtok(NULL, ", \t");

      } // End hz loop

    ++nRecords;
    }

  fclose(inFP);

  // If FlightDate was specified, we need to re-write the base_time & Time::units
  // since we didn't know the start time of the first data record, just the date
  // of the flight.
  WriteBaseTime();

  nc_redef(ncid);
  SetPlainBaseTime();

  sprintf(buffer, "%02d:%02d:%02d-%02d:%02d:%02d",
          startHour, startMinute, startSecond, hour, minute, second);

  status = nc_put_att_text(ncid, NC_GLOBAL, "TimeInterval", strlen(buffer)+1, buffer);
  if (status != NC_NOERR) handle_error(status);
  printf("Time interval completed = %s\n", buffer);
  status = nc_enddef(ncid);
  if (status != NC_NOERR) handle_error(status);
  nc_close(ncid);

  return(0);

}	/* END MAIN */

/* -------------------------------------------------------------------- */
static void WriteMissingData(int currSecond, int lastSecond)
{
  float	dataValue;

  for (int i = lastSecond; i < currSecond; i += BaseDataRate, ++nRecords)
  {
    dataValue = (float)(nRecords * BaseDataRate);
    status = nc_put_var1_float(ncid, timeOffsetID, &nRecords, &dataValue);
    if (status != NC_NOERR) handle_error(status);

    dataValue = MISSING_VALUE;

    for (int j = 0; j < nVariables; ++j)
      status = nc_put_var1_float(ncid, varid[j], &nRecords, &dataValue);
      if (status != NC_NOERR) handle_error(status);
  }
}	/* END WRITEMISSINGDATA */

/* -------------------------------------------------------------------- */
static int ProcessArgv(int argc, char **argv)
{
  int	i;

  for (i = 1; i < argc; ++i)
  {
    if (argv[i][0] != '-')
      break;

    switch (argv[i][1])
    {
      case 'b':
        if (strlen(FlightDate) > 0)
          fprintf(stderr, "-d option trumps -b option, BaseTime ignored.\n");
        else
          BaseTime = atoi(argv[++i]);
        break;

      case 'd':
        {
        struct tm tm;
        strptime(argv[++i], "%F", &tm);
        tm.tm_hour = tm.tm_min = tm.tm_sec = 0;
        BaseTime = mktime(&tm);
        sprintf(FlightDate, "%02d/%02d/%4d", tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900);
        }
        break;

      case 'm':
        secondsSinceMidnight = true;
        break;

      case 'a':
        fileType = NASA_AMES;
        secondsSinceMidnight = true;
        break;

      case 'h':
	histogram = true;
	break;

      case 'c':
	fileType = BADC_CSV;
	secondsSinceMidnight = true;
	break;

      case 'i':
        fileType = ICARTT;
        secondsSinceMidnight = true;
        break;

      case 'l':
        fileType = NASA_LANGLEY;
        secondsSinceMidnight = true;
        break;

      case 'g':
        globalAttrFile = argv[++i];
        break;

      case 'r':
        {
        float rate = atof(argv[++i]);
        if (rate < 1.0)
          BaseDataRate = (int)(1.0 / rate + 0.5);
        if (rate > 1.0)
          dataRate = (int)rate;
        }
        break;

      case 's':
        SkipNlines = atoi(argv[++i]);
        break;

      case 'v':
        verbose = true;
        break;

      case ':':
        Colonless = true;
        break;

      default:
        fprintf(stderr, "Invalid option %s, ignoring.\n", argv[i]);
    }
  }

  return(i);

}	/* END PROCESSARGV */
/* -------------------------------------------------------------------- */
size_t ProcessTime(char *p)
{
    if (secondsSinceMidnight)
      {
      /* Save the seconds with any possible subsecond component */
      currSecond = atof(p);

      hour = int(currSecond) / 3600; currSecond -= hour * 3600;
      minute = int(currSecond) / 60; currSecond -= minute * 60;
      second = int(currSecond);

      if (nRecords == 0 && fileType != PLAIN_FILE)
        SetNASABaseTime(hour, minute, second);
      }
    else
      {
      if (Colonless)
        {
	/* Save the seconds with any possible subsecond component */
	currSecond = atof(&p[4]);
        second = atoi(&p[4]); p[4] = '\0';
        minute = atoi(&p[2]); p[2] = '\0';
        hour = atoi(p);
        }
      else
        sscanf(p, "%d:%d:%lf", &hour, &minute, &currSecond);
        second = int(currSecond);
      }

    if (dataRate > 1) 
      {
      /* parse out the subseond component */
      currSecond -= second; subsec = int(currSecond*dataRate);
      }
    else
      {
      subsec = 0;
      }

    if (hour > 23)
      hour -= 24;

    currSecond = hour * 3600 + minute * 60 + second;


    if (prevSecond == -1) // 1st time through loop.
    {
      firstSecond = int(currSecond);
    }

    // Watch for midnight wrap around.
    if (currSecond < firstSecond)
      currSecond += 86400;

    if (nRecords == 0)
      {
      startHour = hour;
      startMinute = minute;
      startSecond = second;
      }
    else
    if (currSecond == prevSecond  && dataRate <= 1)
      {
      printf("Duplicate time stamp, ignoring, utsecs = %ld\n", (long int)currSecond);
      prevSecond = int(currSecond);
      return(-1);
      }
    else
    if (currSecond > prevSecond + BaseDataRate)
      {
      if (currSecond - prevSecond > 2)
        printf("last time = %d, new time = %d\n", prevSecond, int(currSecond));
//      WriteMissingData(currSecond, prevSecond);
      }

    prevSecond = int(currSecond);
    dataValue = currSecond;
    size_t rec = int(dataValue) - firstSecond;
    status = nc_put_var1_float(ncid, timeVarID, &rec, &dataValue);
    if (status != NC_NOERR) handle_error(status);
    status = nc_put_var1_float(ncid, timeOffsetID, &rec, &dataValue);
    if (status != NC_NOERR) handle_error(status);

    return(rec);
}	/* END PROCESSTIME */

/* END ASC2CDF.C */
