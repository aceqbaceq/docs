#!/bin/bash

sum=0; 
sum_array=();

for i in $(seq 0 1 60);  do 
    wi=$( bc -l <<< "scale=11; e(-$i/12)") 
    printf  "t=%-4s %-.2f \n"      "$(( i*5 ))"     $( tr "." "," <<< "$wi")
    sum=$(bc <<< "scale=11; $sum+$wi")
    [[ "$i" -gt  0   &&  $(( "$i" %  12 )) -eq 0  ]] &&  { printf  "минута %s\nsum=%.3f\n------\n"   "$(( i/12 ))" $( tr "." "," <<< "$sum" ) ; sum_array+=( "$sum" ); let sum=0; } 
done



megasumma=0; for i in ${sum_array[@]}; do  megasumma=$( bc <<< "scale=11; $megasumma + $i"); done

echo ""
for i in ${sum_array[@]}; do
    printf  "sum(i)=%.2f | %.2f%% \n"    "$( tr '.' ',' <<< $i )"    "$( bc <<< "scale=11; 100*$i/$megasumma" | tr  '.' ',' )"
done




