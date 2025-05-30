#!/bin/bash

[[ -f "./la-data.log" ]] && true > "./la-data.log"


for i in $(seq 0 5 $(( 75*60 )) ); do
    printf "%6i  %s %s %s %s \n"   "$i"     $(     ps -A -L -o cmd,stat  | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" |  sed 's/\(.*\)\( .*$\)/\2/' | grep -E "R|D" | wc -l          )       $( awk '{print $1}' < /proc/loadavg ) $( awk '{print $2}' < /proc/loadavg ) $( awk '{print $3}' < /proc/loadavg ) | tee -a ./la-data.log
    sleep 5
done

