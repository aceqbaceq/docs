#!/bin/bash


#
# основные переменные
#
f_m="90"  # сколько даннных для начала нужно набрать в минутах
r=();la_p=0;la_now=0;b_t_1min=0;la_m1min=0;b_t_5s=0;b_t_5s_array=();
size_f_m="$(( $f_m*12 + 1 ))";




#
# функции
#
function initialize_arrays  {
    size_r="$size_f_m"   


    for i in $(seq 0 1 $(( $size_f_m-1 ))  ); do
        r+=( "0"   )           ; 
    done
}



function initialize_palki {
    dlinna="60"
    palki=$( for i in $(seq 1 1 $dlinna); do echo -en "|"; done   );  tochki=$( for i in $(seq 1 1 $dlinna); do echo -en "."; done   ); # переменные визуалиаззации

}




function progress_bar {
    
    #b_t_5min="1.6"
    local busy=$( bc <<< "scale=5; $dlinna * ($b_t_5min/100) " | cut -d"." -f1   ); [[ -z "$busy" ]] && busy="0"; \
                                   [[ $( bc <<< "scale=11; $busy>=($dlinna-1)"   )  -eq 1   ]]  && busy="$dlinna" ; # echo "$busy" ; 
    local idle=$( bc <<<  "scale=5; $dlinna - $busy " | cut -d"." -f1  );  # echo $busy $idle

    b_t_5min_graph=$(    echo -en "["; \
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
sleep 5; 
printf "Инициализация ...1/1\n" 





#
# главное тело рабочее
#
while true; do  

    r=( ${r[@]:1:$size_r} ); 


    r+=( $( ps -A -L -o cmd,stat  | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" | sed 's/\(.*\)\( .*$\)/\2/' | grep -E "R|D" | wc -l   )  )   ;  
    la_proc=$(cat /proc/loadavg | awk '{print $3}'); la_m1min="$la_p" # la прочитанный из proc
    r_sr_5min_pr=0; for i13  in ${r[@]}; do  r_sr_5min_pr=$(    bc <<< "scale=4; $r_sr_5min_pr+$i13/$size_f_m    ");   done;
    b_t_5min=0; for i in ${r[@]}; do  [[ "$i" -ne "0"  ]]  &&   b_t_5min=$(    bc <<< "scale=4; $b_t_5min+100/$size_f_m    ");   done;   



    progress_bar


   printf  " r=%-30s                                                                                                          | %.1f%% %s\n la_proc=%s  | r_sr_1min_pr=%5.2f %s \n\n"                               \
                                     " ${r[*]}"    \
                                     $( tr "." "," <<< "$b_t_5min" )   \
                                     "$b_t_5min_graph" \
                                     "$la_proc" \
                                      $( tr "." "," <<< "$r_sr_5min_pr" )  \
                                      | tr "," "." 








    sleep 5


done;  
exit 0


###############################################################################
# конец
###############################################################################




