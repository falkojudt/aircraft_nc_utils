#!/bin/csh -x

setenv JNC2ASC /opt/local/lib/nc2Asc

java  -cp ${JNC2ASC}/nc2Asc.jar:${JNC2ASC}/netcdfUI-2.2.22.jar:${JNC2ASC}/nlog4j-1.2.25.jar:${JNC2ASC}/commons-logging-1.1.jar  edu.ucar.eol.nc2Asc.NC2A  $* 

