#!/bin/bash


#
# используем EMA1min и LA1min для того чтобы оценить r_sr за 5 минут
#


#
# основные переменные
#
f_m="5"  # сколько даннных для начала нужно набрать в минутах
r=();la_p=0;la_now=0;b_t_5min=0;la_m1min=0;b_t_5s=0;b_t_5s_array=();
size_f_m="$(( $f_m*12 + 1 ))";




#
# функции
#
function initialize_arrays  {
    size_r="$size_f_m"   


    la_p=$(  bc <<< "scale=2; $(cat /proc/loadavg | awk '{print $1}')/1"    )

    r_sr=$la_p ;  # набиваю массив r из r=r_sr
    for i in $(seq 0 1 $(( $size_f_m-1 ))  ); do
        r+=( "$r_sr"   )           ;
    done
}



function initialize_palki {
    dlinna="50"
    palki=$( for i in $(seq 1 1 $dlinna); do echo -en "|"; done   );  tochki=$( for i in $(seq 1 1 $dlinna); do echo -en "."; done   ); # переменные визуалиаззации

}




function progress_bar {
    
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
    r_summa="0"; for i2 in ${r[@]}; do  r_summa=$(    bc <<< "scale=2; $r_summa+$i2    ")   ; done;
    la_now=$( bc <<< "scale=2;     0.92*$la_p+0.08*${r[-1]}     ");
    r_sr_5min_pr=0; for i13  in ${r[@]}; do  r_sr_5min_pr=$(    bc <<< "scale=4; $r_sr_5min_pr+$i13/$size_f_m    ");   done;
    b_t_5min=0; for i in ${r[@]}; do  [[  $(    bc <<< "scale=2; $i>0    ")  -eq 1 ]]  &&   b_t_5min=$(    bc <<< "scale=4; $b_t_5min+100/$size_f_m    ");   done;   



    progress_bar


    printf  " r=%-20s |\n %.1f%% %s\n r_summa=%s ema1min=%s la1min=%s |  ema1min/r_summa=%s%% la1min/r_summa=%s%%  | r_sr_5min_pr=%-5.2f r_sr_5min_pr/r_summa=%s%%   \n\n"                               \
                                     " ${r[*]}"    \
                                     $( tr "." "," <<< "$b_t_5min" )   \
                                     "$b_t_5min_graph" \
                                     "$r_summa" \
                                      $( bc <<< "scale=2; $la_now*12.5" ) \
                                     "$la_now" \
                                      $( bc <<< "scale=2; 100*($la_now*12.5)/$r_summa" ) \
                                      $( bc <<< "scale=2; 100*($la_now)/$r_summa" ) \
                                      $( tr "." "," <<< "$r_sr_5min_pr" )  \
                                      $( bc <<< "scale=2; 100*($r_sr_5min_pr)/$r_summa" )  \
                                      | tr "," "." 







    la_p="$la_now"
    sleep 5


done;  
exit 0


###############################################################################
# конец
###############################################################################




