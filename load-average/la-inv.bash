#!/bin/bash
a=0;

r=1; p="0.92"; min=5; 

for i in $(seq 0 1 $(($min*12))); do  



    a=$(  bc <<< "scale=11; $p*$a + $r"  );

    q=$(bc<<<"scale=2;1-$p");              
    [[ "$( bc <<< "scale=11; $q*$a>=0.99" )" -eq 1 ]] && { break ; }   


    echo -e "r=$r a=$a" "a*$q%="$(bc<<<"scale=2;$q*$a"); 

    let t=$t+1;  (( "$t" % "12" )) ||  echo -e "-->  +1min\np=$p";

done; 

echo "";
