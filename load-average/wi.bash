#!/bin/bash


#
# инциализация
#
minutes=8
FN="./wi.log"; [[ -f "$FN" ]] && true > "$FN"
sum=0; 
sum_array=();
wi_array=();
wixi_array=()
xi_array=()





#
# формирую временный wi массив но по времени задом наперед
#
wt_array=()
for i in $(seq 0 1 $(( $minutes*12 )) );  do
    wt=$( bc -l <<< "scale=11; e(-$i/12)"); wt_array+=(  "$wt"    )
done
#
# промежуточная задача
# хочу узнать  сумму wi за последние $mm минут
#
summa="0"; mm=5;
for i in $(seq 0 1 $(( $mm*12   )) );  do
    summa=$( bc <<< "scale=11;  $summa+${wt_array[$i]}" );

done
echo "сумма wi за послдение $mm минут = $summa"




#
# разворачиваю wi по времени так как надо тоесть бОльший коэфциент должен быть самый последний по времени
#
for i in $(seq $(( $minutes*12 )) -1 0);  do
    wi_array+=(  "${wt_array[$i]}" );
done





#
# вычисляю wi*xi
#
for i in $(seq 0 1 $(( $minutes*12 )) );  do
     #xi=0
     #xi=$( bc -l <<< "1*s((2*3.14)*($i*5-(-0.175)*60)*(1/60)/0.5)" )
     #xi=$( bc -l <<< "1*s((2*3.14)*($i*5-(-5.5)*60)*(1/60)/12)" )
     #xi=$( bc -l <<< "1*s((2*3.14)*($i*5-(-9.7)*60)*(1/60)/15)" )
     xi=$( bc -l <<< "1*s((2*3.14)*($i*5-(0)*60)*(1/60)/16)" )
     #xi=$( bc -l <<< "1*s((2*3.14)*($i*5-(4.1)*60)*(1/60)/20)" )
     #xi=$( bc -l <<< "1*s((2*3.14)*($i*5-(-6.0)*60)*(1/60)/40)" )
    #xi=1
     [[  "$i" -gt "48"   ]] && xi="0"
    #printf  "t=%-4s %-.2f \n"      "$(( i*5 ))"     $( tr "." "," <<< "${wi_array[$i]}")
    wixi=$(bc <<< "scale=11; ${wi_array[$i]}*$xi"); wixi_array+=( "$wixi"   ); printf "%s %.4f %s \n"  "$(( i*5 ))"   $( tr "." "," <<< "$wixi" )  "$xi"   | tr "," "."  >> "$FN"
    sum=$(bc <<< "scale=11; $sum+$wixi")
    [[ "$i" -gt  0   &&  $(( "$i" %  12 )) -eq 0  ]] &&  { printf  "минута %s\nsum=%.3f\n------\n"   "$(( i/12 ))" $( tr "." "," <<< "$sum" ) ; sum_array+=( "$sum" ); let sum=0; } 
done




megasumma=0; 
for i in ${sum_array[@]}; do
    temp="$i"
    ((  $(bc <<< "$temp < 0") )) && temp=$( bc <<< "-($temp)"  )
    megasumma=$( bc <<< "scale=11; $megasumma + $temp"); 
done





echo ""
last_sum=$((  ${#sum_array[*]}-1  ))
for i in $(seq 0 1 "$last_sum"); do
    j="${sum_array[$i]}"
    printf  "%3s | sum(i)=%.2f | %.2f%% \n"   "$((i+1))"    "$( tr '.' ',' <<< $j )"    "$( bc <<< "scale=11; 100*$j/$megasumma" | tr  '.' ',' )"
done


echo "==============================="
LA="0"
for i in $(seq 0 1 $(( $minutes*12 )) );  do
    LA=$(bc <<< "scale=11; $LA+${wixi_array[$i]}");
done

printf "LA=%f \n\n"  $( bc <<< "scale=11; $LA/12.5" | tr "."   "," )








