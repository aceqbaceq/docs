#!/bin/bash

FM="./log.txt"
[[ -f "$FM" ]] && true > "$FM"
SL_TIME="5"  # интервал сэмплинга
MAX_TIME="320"  # максимальное число сэмплов которые мы будем собирать



r=(); la=(); by=(); t=( "0" );
for i in $(seq 1 1 12); do
#    r+=( $( ps -L a -o stat,cmd | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" | wc -l )  )
    r+=( $( vmstat 1 | head -n4 | tail -n1  | awk '{print $1}')  )


    la+=( $( cat /proc/loadavg | awk '{print $1}')  )
#    by+=(  $( bc <<< "scale=2;  100 - $(vmstat 1 | head -n4 | tail -n1 | awk '{print $15}') " )    )
     by+=( "0" )

    echo "${t[-1]} ${r[-1]} ${la[-1]} - ${by[-1]}" >>  "$FM"
    echo "набираю 12 точек...$i/12"
    sleep "$SL_TIME"; t+=( $(bc <<< "${t[-1]} + 5")  )

done


#echo -e "r=${r[*]} | la=${la[*]}" "\n"
#echo -e "by=${by[*]}"  "\n"
#exit 1



for i in $(seq "$MAX_TIME"); do
#    r+=( $( ps -L a -o stat,cmd | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" | wc -l )  );
     r+=( $( vmstat 1 | head -n4 | tail -n1 | awk '{print $1}')  )


    la+=( $( cat /proc/loadavg | awk '{print $1}')  );  
#    by+=(    $( bc <<< "scale=2; 100 - $( vmstat 1 | head -n4 |  tail -n1 | awk '{print $15}') " )     )
    by+=( "0" )

    avg_13=0; 
    for i in $(seq 0 1 "$(( ${#r[*]}-1 ))" ); do    avg_13=$( bc <<< "scale=2; $avg_13+(${r[$i]}/13)"  );     done
    echo "${t[-1]} ${r[-1]} ${la[-1]} $avg_13 ${by[-1]} " >>  "$FM";


    echo " t | r | la | sma | busy |"
    for i in $(seq 0 1 "$(( ${#r[*]}-2 ))" ); do  echo "${t[$i]}  ${r[$i]} ${la[$i]} -  ${by[$i]}"; done;  echo "${t[-1]} ${r[-1]} ${la[-1]} $avg_13 ${by[-1]} "; echo -e "\n";

    r=( ${r[@]:1} ); la=( ${la[@]:1} ); t=( ${t[@]:1} ); by=( ${by[@]:1} ); 

    sleep "$SL_TIME"; t+=( $(bc <<< "${t[-1]} + 5")  )

done



