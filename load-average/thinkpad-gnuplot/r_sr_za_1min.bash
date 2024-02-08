#!/bin/bash


#
# основные переменные
#
f_m="1"  # сколько даннных для начала нужно набрать в минутах
r=();la_p=0;la_now=0;b_t_1min=0;la_m1min=0;b_t_5s=0;b_t_5s_array=();
size_f_m="$(( $f_m*12 + 1 ))";




#
# функции
#
function initialize_arrays  {
    size_r="$size_f_m"   
    size_la_now_array="$size_f_m"
    size_b_t_5s_array="$size_f_m"


    for i in $(seq 0 1 $(( $size_f_m-1 ))  ); do
        r+=( "0"   )           ; 
	la_now_array+=( "0" )  ;
	b_t_5s_array+=( "0" )  ;
    done
}


function initialize_palki  {
    dlinna="50"
    palki=$( for i in $(seq 1 1 $dlinna); do echo -en "|"; done   );  tochki=$( for i in $(seq 1 1 $dlinna); do echo -en "."; done   ); # переменные визуалиаззации


}



function progress_bar {
    local busy=$( bc <<< "scale=5; $dlinna * ($b_t_1min/100) " | cut -d"." -f1   );   \
                 [[ -z "$busy" ]] && busy="0";  \
                 [[ $( bc <<< "scale=11; $busy>=($dlinna-1)"   )  -eq 1   ]]  && busy=$dlinna ; # echo $busy
    local idle=$( bc <<<  "scale=5; $dlinna - $busy " | cut -d"." -f1  );  # echo $busy $idle

    b_t_1min_graph=$(    echo -en "["; \
	                 echo -en  ${palki:0:$busy };\
    	                 echo -en  ${tochki:0:$idle };\
        	         echo "]" \
            	     );
}





#
# основная иницилизация
#
printf "Инициализация ...0/1\r" 
initialize_arrays
initialize_palki
la_p=$(cat /proc/loadavg | awk '{print $1}'); la_m1min="$la_p" # la предыдущий
sleep 5; 
printf "Инициализация ...1/1\n" 





#
# главное тело рабочее
#
while true; do  

    r=( ${r[@]:1:$size_r} ); 
    la_now_array=( ${la_now_array[@]:1:$size_la_now_array} ); la_m1min="${la_now_array[0]}"
    b_t_5s_array=( ${b_t_5s_array[@]:1:$size_b_t_5s_array} ); #echo  "size_b_t_5s_array=$size_b_t_5s_array"


    r+=( $( ps -A -L -o cmd,stat  | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" | sed 's/\(.*\)\( .*$\)/\2/' | grep -E "R|D" | wc -l   )  )   ;  
    la_now=$( bc <<< "scale=2;     0.92*$la_p+0.08*${r[-1]}     "); la_now_array+=( "$la_now" );
    la_proc=$(cat /proc/loadavg | awk '{print $1}'); la_m1min="$la_p" # la прочитанный из proc
    r_sr_1min_pr=0; for i13  in ${r[@]}; do  r_sr_1min_pr=$(    bc <<< "scale=4; $r_sr_1min_pr+$i13/$size_f_m    ");   done;


    [[  $( bc <<< "scale=2;     $la_p == 0   ")    -eq 1  ]]  &&   b_t_5s_array+=( "0" ) 
    [[  $( bc <<< "scale=2;     $la_p > 0   ")    -eq 1  ]]  &&   \
                  {    [[   $( bc <<< "scale=2;     100*(-$la_now+$la_p)/$la_p   >= 7     ")    -eq 1  ]]  &&   b_t_5s_array+=( "0" ) ||  b_t_5s_array+=( "1" );   }


    b_t_1min=0; for i in ${b_t_5s_array[@]}; do  [[ "$i" -eq "1"  ]]  &&   b_t_1min=$(    bc <<< "scale=4; $b_t_1min+100/$size_f_m    ");   done;   #echo "    ${b_t_5s_array[*]}"



    progress_bar


   printf  " r=%-20s | la_now=%.2f | r_sr_1min_r=%5.2f | r_sr_1min_pr=%5.2f %s \n"                               \
                                     " ${r[*]}"    \
                                      $( tr "." "," <<< "$la_now" )     \
                                      $( tr "." "," <<< $( bc -l  <<< "scale=2;     ( $la_now-$la_m1min/e(1) )/0.66     ")  )  \
                                      $( tr "." "," <<< "$r_sr_1min_pr" )  \
                                      "$b_t_1min_graph" \
                                      | tr "," "." 
   







    la_p="$la_now"
    sleep 5


done;  
exit 0


###############################################################################
# конец
###############################################################################




