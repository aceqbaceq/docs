#!/bin/bash

FN="./wi_small.log"; [[ -f "$FN" ]] && true > "$FN"

#zeros_min=6; zeros=(); for i in $(seq 0 1 $(( "$zeros_min"*12 -1)) ); do zeros+=( "0" ); done ;
#ones_min=1; ones=(); for i in $(seq 0 1 $(( "$ones_min"*12 )) ); do ones+=( "1" ); done ;
zeros=("0");
ones=("1 1 1 1 1 1 1 1 1 1 1 1 1")
r=( ${zeros[@]} ${ones[@]} )
r_last_index=$(( ${#r[*]}-1 )); # echo  -e "r_last_index=$r_last_index\n"

p=$(  bc -l <<< "scale=11; e(-1/12)"  );  
summa_wixi=0; 
summa_wi=0;
j="0"






#
# summa(wi*xi)
#
for i in $(seq $r_last_index -1 0); do 

    wi=$( bc <<< "scale=11; $p^$j"); #printf "j=%d wi=%.3f \n"    "$j"   
    xi="${r[$i]}";  printf "%d %.3f \n"   "$(( i*5 ))"   $( tr "." "," <<< "$xi") | tr "," "."  >> "$FN"
    summa_wixi=$(  bc <<< "scale=11; $summa_wixi+$wi*$xi"  ); 


    let j=$j+1
done; 


#
# summa(wi)
#
j=0
for i in $(seq $r_last_index -1 0); do 

    wi=$( bc <<< "scale=11; $p^$j"); 
    summa_wi=$(  bc <<< "scale=11; $summa_wi+$wi"  ); 

    let j=$j+1
done; 
printf "\nsumma_wi=%.3f \n"   $( tr "." "," <<< "$summa_wi") | tr "," "."




#
# LA
#
LA=$(  bc <<< "scale=11; $summa_wixi/$summa_wi"  ); printf "\nLA=%.3f \n\n"    $( tr "." "," <<< "$LA") | tr "," "."





