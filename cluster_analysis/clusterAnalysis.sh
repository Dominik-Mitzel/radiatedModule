#!/bin/bash

#This is a documentation for the measurement of the reflectivity of different mirrors tested for SciFi
#Basically this script executes everything to get the light yield for given datarun with pedestal
#The gain is Fitted directly from the data peaks with gainAnalysis.cc in gainAnalysisData. The folder for Data files is set to:
#/home/scifi_testbeam14/MirrorStudy/
#The name of the pedestal file has to be of the form : btsoftware_<runnumber>_calib_dark_ntuple.root                                                                      
#And the Datarun file: btsoftware_<runnumber>_datarun_ntuple.root 
#Target folder for gain File is /home/scifi_testbeam14/MirrorStudy/led_gain/fromData/

doGainAnalysis=true

files_uplink10=( 1028 ) #2027 3027 4027 ) #2026 3026 ) 
files_uplink11=( 4126 ) #2126 3126 ) 
files_uplink12=( 4226 ) #2226 3226 ) 
files_uplink13=( 4326 ) #2326 3326 ) 


if $doGainAnalysis; then 
 
    for i in "${files_uplink10[@]}"
    do
	let pedestal=$i*10+1
	let led=$i*10+2
	let data=$i*10+3
	file=$i'X.txt'
	echo -e "$pedestal \t $led \t $data" > $file 
	echo 'file '$led' for gain measurement'
	#../gainAnalysisData/gainAnalysis --l $led --u 10
    done 
    
    for i in "${files_uplink11[@]}"
    do
	let pedestal=$i*10+1
	let led=$i*10+2
	let data=$i*10+3
        file=$i'X.txt'
        echo -e "$pedestal \t $led \t $data" > $file
	echo 'file '$led' for gain measurement'
	#../gainAnalysisData/gainAnalysis --l $led --u 11
    done

    for i in "${files_uplink12[@]}"
    do
	let pedestal=$i*10+1
	let led=$i*10+2
	let data=$i*10+3
        file=$i'X.txt'
        echo -e "$pedestal \t $led \t $data" > $file
	echo 'file '$led' for gain measurement'
	#../gainAnalysisData/gainAnalysis --l $led --u 11
    done

    for i in "${files_uplink13[@]}"
    do
	let pedestal=$i*10+1
	let led=$i*10+2
	let data=$i*10+3
        file=$i'X.txt'
        echo -e "$pedestal \t $led \t $data" > $file
	echo 'file '$led' for gain measurement'
	#../gainAnalysisData/gainAnalysis --l $led --u 11
    done

fi

##light yield

for i in "${files_uplink10[@]}"
  do 
    file=$i'X.txt'
    targetFile=txtFiles/results/$i'X_results.txt'
    echo 'taking file :'$file ' for light yield measurement measurement'
   # ./cluster_analysis --l $file --c 0 10 11 12 13 
done

for i in "${files_uplink11[@]}"
  do
    file=$i'X.txt'
    targetFile=txtFiles/results/$i'X_results.txt'
    echo 'taking file :'$file ' for light yield measurement measurement'
    #./cluster_analysis --l $file --c 1 10 11 12 13 
done

for i in "${files_uplink12[@]}"
  do
    file=$i'X.txt'
    targetFile=txtFiles/results/$i'X_results.txt'
    echo 'taking file :'$file ' for light yield measurement measurement'
    ./cluster_analysis --l $file --c 2 10 11 12 13 
done

for i in "${files_uplink13[@]}"
  do
    file=$i'X.txt'
    targetFile=txtFiles/results/$i'X_results.txt'
    echo 'taking file :'$file ' for light yield measurement measurement'
    ./cluster_analysis --l $file --c 3 10 11 12 13 
done












