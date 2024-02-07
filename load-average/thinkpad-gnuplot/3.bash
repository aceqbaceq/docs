#!/bin/bash

timeout="60"
max_proc="7"


while true; do  
    p_n=$( ps aux | grep stress | wc -l  ) ; echo "p_n=$p_n"

    if [[ "$p_n" -lt "6"   ]] ; then
	  echo "добавляю процессы";   
	  n=$( shuf -i 1-$max_proc -n 1 ); 


		for i in $(seq 0 1 "$n"); do 
			stress --quiet  --cpu 1 --timeout $( shuf -i 6-30 -n 1  ) & 
		done;  
	    echo "новые $n процессы добавлены"

    fi  

    echo "сплю $timeout секунд"; sleep "$timeout";  

done

