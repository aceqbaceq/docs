#!/bin/bash


#
# инициализщация
#
f_m="1"  # сколько даннных для начала нужно набрать в минутах
r=(); b_t=();
b_t_enabled="0" #нужно ли считать busy time cpu



####################################################################
#  ПЕРВЫЙ БЛОК
#  готовлю первую $f_m  минут
#

la_p=$(cat /proc/loadavg | awk '{print $1}') # la практический

for i in $(seq 0 5 $(( $f_m*60)) ); do  
    r+=( $( ps -A -L -o cmd,stat  | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" | sed 's/\(.*\)\( .*$\)/\2/' | grep -E "R|D" | wc -l   )  )   ; 
    [[ "$b_t" -eq 1 ]]  &&  b_t+=(   $((   100 - $( tail -n1 busytime.txt  | awk '{print $15}' )   ))    ) || b_t=( ) # echo "${b_t[*]}"
    printf "Инициализация ...$i/$(( $f_m*60  ))\r" 
    sleep 5; 
done; echo ""




summa=0; 
for i in "${r[@]}"; do
    summa=$(( "$summa"+"$i" ))
    la_r=$( bc <<< "scale=2; $summa/($f_m*12)     ")


done

oshibka=$( bc <<< "scale=11; 100 *  ($la_p-$la_r)/($la_p)  | tr "." ","   ")    # то наскоьлько расчетный la неспадает с практическим



if [[ "$b_t" -eq "1" ]]; then
    summa_b_t=0;
    for i in "${b_t[@]}"; do
	summa_b_t=$(( "$summa_b_t"+"$i" ))
	b_t_5min=$( bc <<< "scale=2; $summa_b_t/($f_m*12)     ")


    done

else 
    b_t_5min=0
fi



printf  "r=%s | la_comp=%s la_r=%.2f b_t_5min=%s osh.=% 0.0f \n"               \
                                                         "${r[*]}"    \
                                                         "$la_p"      \
                                                          $( tr "." "," <<< "$la_r" )  \
                                                          "$b_t_5min" \
                                                          "$oshibka"    \
                                                          | tr "," "." 




#
#  ПЕРВЫЙ БЛОК
#  готовлю первую $f_m  минут
#  КОНЕЦ
#########################################################################
#exit 1








########################################################################
# ВТОРОЙ БЛОК
# дальнейшая часть 
#
last_el="${#r[*]}";  
[[ "$b_t" -eq "1" ]] && last_b_t="${#b_t[*]}";  

while true; do  

    la_p=$(cat /proc/loadavg | awk '{print $1}') # la практический


    # r block
    r=( ${r[@]:1:$last_el} )
    r+=( $( ps -A -L -o cmd,stat  | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" | sed 's/\(.*\)\( .*$\)/\2/' | grep -E "R|D" | wc -l   )  )   ; 


    summa=0
    for i in "${r[@]}"; do
	summa=$(( "$summa"+"$i" ))
	la_r=$( bc <<< "scale=2; $summa/($f_m*12)     ")
    done

    oshibka=$( bc <<< "scale=11; 100 *  ($la_p-$la_r)/($la_p)     "  | tr "." ","  )   # то наскоьлько расчетный la неспадает с практическим


    # b_t block
    if [[ "$b_t" -eq "1" ]]; then
	b_t=( ${b_t[@]:1:$last_b_t} )
	b_t+=(   $((   100 - $( tail -n1 busytime.txt  | awk '{print $15}' )   ))    ); # echo "${b_t[*]}"


	summa_b_t=0;
	for i in "${b_t[@]}"; do
	    summa_b_t=$(( "$summa_b_t"+"$i" ))
	    b_t_5min=$( bc <<< "scale=2; $summa_b_t/($f_m*12)     ")


	done
    else
	b_t_5min="0"
    fi




    # print 
    printf  "r=%s | la_comp=%s la_r=%.2f b_t_5min=%s osh.=%.0f \n"               \
                                                         "${r[*]}"    \
                                                         "$la_p"      \
                                                          $( tr "." "," <<< "$la_r" )  \
                                                          "$b_t_5min" \
                                                          "$oshibka"    \
                                                          | tr "," "." 





    sleep 5; 
done; 

#
#  ВТОРОЙ БЛОК
#  
#  КОНЕЦ
#########################################################################


