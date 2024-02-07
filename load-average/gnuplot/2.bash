#!/bin/bash

FN="./2-la.out"; [[ -f "$FN" ]] &&  true > "$FN"
minute="1"
s="5"
la_ar=();

FN2="./2-r.out"; [[ -f "$FN2" ]] &&  true > "$FN2"
r_ar=()

#formula="0.0092*$t+0.64"



for t in $(seq 0 $s $(($minute*60))); do

    la=$( bc <<< "scale=11; 0.0092*$t+0.64     " ); la_ar+=( "$la"   );
    
    echo "$t $la" >> "$FN"

done





for t in $(seq $s $s $(($minute*60))); do

    r=$(   bc <<< "  scale=11;      ( ${la_ar[ $(( $t/$s )) ]}  - 0.92*${la_ar[ $(( ($t-$s)/$s )) ]}  ) / 0.08  "  );   r_ar+=( "$r" )
    
    echo "$t $r" >> "$FN2"

done





