#led runs
array=(
#10252
#13252
#11262
#12262    
#20262
#21262
#22262
#23262
#30262
#31262
#32262
#33262
#40262
#41262
42262
43262
)


for i in  ${array[@]} 
do

./gainAnalysis --l $i --u 10
./gainAnalysis --l $i --u 11
./gainAnalysis --l $i --u 12
./gainAnalysis --l $i --u 13

done

