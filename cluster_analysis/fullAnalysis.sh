#!/bin/bash                                                                                                                                                                                 

FILE=$1

#do gain calculaation 

while read first second third 
do 
    echo "Doing gain anaysis with file $second..." 
    echo "uplink 10.."
    ./home/scifi_testbeam14/sw/tools/radiatedModule/gainanalysis/gainanalysis --l $second --u 10
    echo "uplink 11.."
    ./home/scifi_testbeam14/sw/tools/radiatedModule/gainanalysis/gainanalysis --l $second --u 11
    echo "uplink 12.."
    ./home/scifi_testbeam14/sw/tools/radiatedModule/gainanalysis/gainanalysis --l $second --u 12
    echo "uplink 13.."
    ./home/scifi_testbeam14/sw/tools/radiatedModule/gainanalysis/gainanalysis --l $second --u 13
    echo "Now running cluster analysis with $first $second and $third"
    ./cluster_analysis --l $1 --c 
   
done < $FILE
