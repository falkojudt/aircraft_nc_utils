package nc2AscData;
import java.lang.*;
import java.util.zip.*;
import java.util.*;
import java.text.*;
import java.io.*;

public class DataFmt {

	public final static String NODATE = "No Date";
	public final static String DATESPACE = "yyyy mm dd";
	public final static String DATEDASH = "yyyy-mm-dd";

	public final static String TIMESPACE = "hh mm ss";
	public final static String TIMECOLON = "hh:mm:ss";
	public final static String TIMENOSPACE = "hhmmss";
	public final static String TIMESEC = "sec of day"; 

	public final static String MISSVAL = "-32767.0";
	public final static String REPLICATE = "Replicate";
	
	public final static String FULLTM = "Full";

	public final static String HEAD = "Head";
	public final static String HEAD2 = "Head2";
	public final static String HEAD3 = "Head3";
 
	public final static String DATESTR ="Date";
	
	public final static int HEAD_IDX = 0;
	public final static int AVG_IDX = 1;
	public final static int DATE_IDX = 2;
	public final static int TM_IDX = 3;
	public final static int DMTR_IDX = 4;
	public final static int MVAL_IDX = 5;
	public final static int TMSET_IDX = 6;
	
	public final static String SEPDELIMIT =",";
	public final static String SPACE =" ";
	public final static String TMSETDELIMIT= "~";
	public final static String TMSETCOLON= ":";

	private static String[] dataFmt = new String[7]; 
	//private StringBuffer data = new StringBuffer();

	public DataFmt() {
		initDataFmt();
	}

    public void initDataFmt() {
    	dataFmt[DATE_IDX]=DATEDASH.toString();
		dataFmt[TM_IDX]=TIMECOLON.toString();
		dataFmt[DMTR_IDX]=",";
		dataFmt[MVAL_IDX]=MISSVAL.toString();
		dataFmt[TMSET_IDX]=FULLTM.toString(); //timeset= 00:00:00~99:99:99[
		dataFmt[HEAD_IDX]=HEAD.toString();
		dataFmt[AVG_IDX]="1";
    }
	
	/**
	 * The method is for users to record the desired data format in the class
	 * for further data formatting.
	 * @param  s    -    selected data format
	 * @param idx	-    position in data format string 
	 */
	public static void setDataFmt(String s, int idx){
		dataFmt[idx] = s;
	}

	/**
	 * This is for users to retrieve the desired data format in simple form
	 * @return dataFmt
	 */
	public String[] getDataFmt(){
		return dataFmt;
	}
	
	/**
	 * This is for users to retrieve the desired data format in simple form
	 * @return dataFmt
	 */
	public String[] getNewDataFmt(){
		//return dataFmt;
		String[] dfmt = new String[7];
		if (dataFmt[DATE_IDX]==DATEDASH) {
			dfmt[DATE_IDX]="-";
		}  else if (dataFmt[DATE_IDX]==DATESPACE) {
			dfmt[DATE_IDX]=" ";
		} else {
			dfmt[DATE_IDX]= dataFmt[DATE_IDX];
		}
		
		if (dataFmt[TM_IDX]==TIMECOLON) {
			dfmt[TM_IDX]= ":";
		} else if (dataFmt[TM_IDX]==TIMESPACE) {
			dfmt[TM_IDX]= " ";
		} else if (dataFmt[TM_IDX]==TIMENOSPACE) {
			dfmt[TM_IDX]= "";
		} else {
			dfmt[TM_IDX]= dataFmt[TM_IDX];
		}
		
		dfmt[DMTR_IDX]= dataFmt[DMTR_IDX];
		dfmt[MVAL_IDX]=dataFmt[MVAL_IDX];

		//time set
		dfmt[TMSET_IDX]=dataFmt[TMSET_IDX];
		
		dfmt[HEAD_IDX]=dataFmt[HEAD_IDX];
		dfmt[AVG_IDX]=dataFmt[AVG_IDX];
		return dfmt;
		
	}

	public void showNewDataFmt() {
		String[] fstr = getNewDataFmt();
		String str="";
		for (int i=0; i<7; i++) {
	       str += fstr[i]+"     ";
		}
		nc2Asc.NC2Act.wrtMsg(str);
	}
	
	public void showDataFmt() {
		String str="";
		for (int i=0; i<7; i++) {
	       str += dataFmt[i]+"\n";
		}
		nc2Asc.NC2Act.wrtMsg(str);
	}
	
	/**
	 * It takes the time in milli-seconds since Jan.1,1970, then convert it's date
	 * into desired date format
	 * @param ti -- time in milli seconds since jan.1,1970
	 * @return   -- date in required format     //check hour>24

	 */
	public 	String  fmtDate(long ms) throws DataFormatException {
		Calendar d = Calendar.getInstance();
		d.setTimeInMillis(ms); ///calendar takes milli-seconds as paramter

		String[] s = new String[3];
		s[0] = ""+d.get(Calendar.YEAR);
		s[1] = ""+d.get(Calendar.MONTH);
		s[2] = ""+d.get(Calendar.DAY_OF_MONTH); 
		return fmtDate(s);
	};
	
	/**
	 *  
	 * @param dt -- Date string in yyyy-mm-dd format
	 * @return	 -- new date string in desirable format
	 * @throws DataFormatException
	 */
	public String fmtDate(String dt) throws DataFormatException {
		String[] dd = dt.split("-");
		return fmtDate(dd);
	}

	/**     
	 * It takes the date strings, and convert it into desired
	 * date format.
	 * @param s  -  input date strings
	 * @return   -- desired date format based on dataFmt[0]
	 * @throws DataFormatException
	 */
	public String fmtDate(String[] ss) throws DataFormatException {

		if (ss.length != 3){  		//
			throw new DataFormatException("Invalid Date format: "+ss.length); 
		} 

		//check required output format
		if (dataFmt[DATE_IDX].equals(DATESPACE.toString())){
			return ss[0]+ SPACE.toString() + ss[1] + SPACE.toString() + ss[2];
		} else 	if (dataFmt[DATE_IDX].equals(DATEDASH.toString())){
			return ss[0]+ "-" + ss[1] + "-" + ss[2];
		} else {
			return "";
		}
	};

	/**
	 * It takes time in milli-second, then convers it into 
	 * desired data string.
	 * @param tm -- milli-seconds since Jan1,1970
	 * @return - data in desired format
	 */
	public String fmtTm(long ms) throws DataFormatException{

		Calendar d = Calendar.getInstance();
		d.setTimeInMillis(ms); ///calendar takes milli-seconds as paramter

		String[] s = new String[3];
		int h = d.get(Calendar.HOUR_OF_DAY);
		int m = d.get(Calendar.MINUTE); 
		int ss = d.get(Calendar.SECOND);
		s[0] +=h;
		s[1] +=m;
		s[2] +=ss;
		
		return fmtTm(s);
	}

	/**
	 * 
	 * @param tm -- time string in hh:mm:ss format
	 * @return	 -- a new time string in desirable format
	 * @throws DataFormatException
	 */
	public String fmtTm(String tm) throws DataFormatException {
		String[] tt = tm.split(":");
		return fmtTm(tt);
	}
	
	
	/**	return null;
	 * it takes time strings, converts it into desired format
	 * @param ss -- list of hh mm ss
	 * @return
	 * @throws DataFormatException
	 */
	public String fmtTm(String[] ss) throws DataFormatException {
		//check input format -- 
		if (ss.length!=3){  
			throw new DataFormatException("Invalid time format: "+ss); 
		} 
	
		//check required output format
		if (dataFmt[TM_IDX].equals(TIMESPACE.toString())){
			return ss[0] + SPACE.toString()+ ss[1]+SPACE.toString()+ss[2];
		} else 	if (dataFmt[TM_IDX].equals(TIMECOLON.toString())){
			return ss[0]+ TMSETCOLON.toString() + ss[1] + TMSETCOLON.toString() + ss[2];
		} else 	if (dataFmt[TM_IDX].equals(TIMENOSPACE.toString())) {
			return ss[0]+ ss[1] + ss[2];
		} else 	if (dataFmt[TM_IDX].equals(TIMESEC.toString())) {
			int h= Integer.parseInt(ss[0]);//  new Integer(ss[0]).intValue();
			int m= new Integer(ss[1]).intValue();
			int s= new Integer(ss[2]).intValue();
			int sec = h*3600 +m*60+s;
			return ""+sec; 			
		} else {
			throw new DataFormatException("Invalid output time format: "+dataFmt[1]);	
		}
	}
	
	public String fmtDmtr(String data) throws NullPointerException {
		return fmtDmtr(data.split(SEPDELIMIT.toString()));
	}

	public String fmtDmtr(String[] data) throws NullPointerException {
		
		String tmp="";
		int start =0;
		if (dataFmt[DATE_IDX].equals(NODATE.toString())) {start=1;}
		for (int i=start; i<data.length-1; i++){
		//	nc2Asc.NC2Act.wrtMsg("data[i]: "+ data[i]+ " DataFmt.Misval:" + DataFmt.MISSVAL + "DataFmt.Misval-toString:"+DataFmt.MISSVAL.toString() );
			if (data[i]==null || data[i].length()<1 || data[i].equals(DataFmt.MISSVAL)) {
			  data[i]= dataFmt[MVAL_IDX];	
			}
			tmp = tmp+ data[i]+dataFmt[DMTR_IDX];
		}
		return (tmp+ data[data.length-1]); //add last one 
	}

	public String fmtOneLineData(String data ) throws DataFormatException {
		return fmtOneLineData(data.split(SEPDELIMIT.toString()));
	}
	
	//assume --data contains date/yy-mm-dd
	public String fmtOneLineData(String[] data ) throws DataFormatException {
		String[] oneline=data; 
	
		//get date formated first
		if (dataFmt[DATE_IDX].equals(NODATE.toString())) {
			oneline[0]=NODATE.toString();
		} else {
			oneline[0] = fmtDate(data[0].split("-"));
		}
		//format time
		oneline[1] = fmtTm(data[1].split(TMSETCOLON.toString()));
		//add delimiter
		return fmtDmtr(oneline);
	}	
	
	public String formStr (float[] data, int start, int end) {
		String ret=String.valueOf(data[start]);
		for (int i =start+1; i<end; i++){
			ret += DataFmt.SEPDELIMIT.toString()+ data[i];
		}
		return ret;
	}
	
	public String formStr(String data) {
		String[] d = data.split(DataFmt.SEPDELIMIT.toString());
		return formStr(d,0, d.length);
	}
	
	public String formStr(String data, int start, int end) {
		return formStr(data.split(DataFmt.SEPDELIMIT.toString()), start, end);
	}
	
	public String formStr (String[] data, int start, int end) {
		String ret=data[start];
		for (int i =start+1; i<end; i++){
			ret += DataFmt.SEPDELIMIT.toString()+ data[i];
		}
		return ret;
	}
	
	
}