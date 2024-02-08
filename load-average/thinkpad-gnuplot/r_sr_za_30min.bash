#!/bin/bash


#
# используем EMA5min и LA5min для того чтобы оценить r_sr за 30 минут
#



#
# основные переменные
#
f_m="30"  # сколько даннных для начала нужно набрать в минутах
r=();la_p=0;la_now=0;b_t_1min=0;la_m5min=0;b_t_5s=0;b_t_5s_array=();
size_f_m="$(( $f_m*12 + 1 ))";




#
# функции
#
function initialize_arrays  {
    size_r="$size_f_m"   


    la_p=$(  bc <<< "scale=2; $(cat /proc/loadavg | awk '{print $2}')/1"    )

    r_sr=$la_p ;  # набиваю массив r из r=r_sr
    for i in $(seq 0 1 $(( $size_f_m-1 ))  ); do
        r+=( "$r_sr"   )           ;
    done
}



function initialize_palki {
    dlinna="50"
    palki=$( for i in $(seq 1 1 $dlinna); do echo -en "|"; done   );  tochki=$( for i in $(seq 1 1 $dlinna); do echo -en "."; done   ); # переменные визуалиаззации

}


function find_alpha {

    local min=15;
    alpha=$( bc -l <<< "scale=11; e(-5/($min*60) )      "       ) 

}


function progress_bar {
    
    local busy=$( bc <<< "scale=5; $dlinna * ($b_t_30min/100) " | cut -d"." -f1   ); [[ -z "$busy" ]] && busy="0"; \
                                   [[ $( bc <<< "scale=11; $busy>=($dlinna-1)"   )  -eq 1   ]]  && busy="$dlinna" ; # echo "$busy" ; 
    local idle=$( bc <<<  "scale=5; $dlinna - $busy " | cut -d"." -f1  );  # echo $busy $idle

    b_t_30min_graph=$(    echo -en "["; \
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
find_alpha
sleep 5; 
printf "Инициализация ...1/1\n" 





#
# главное тело рабочее
#
while true; do  

    r=( ${r[@]:1:$size_r} ); 


    r+=( $( ps -A -L -o cmd,stat  | grep -E "R|D" | grep -v -E "STAT|bash|grep|ps|wc" | sed 's/\(.*\)\( .*$\)/\2/' | grep -E "R|D" | wc -l   )  )   ;  
    r_summa="0"; for i2 in ${r[@]}; do  r_summa=$(    bc <<< "scale=2; $r_summa+$i2    ")   ; done;
    la_now=$( bc <<< "scale=2;     ($alpha)*$la_p+(1-$alpha)*${r[-1]}     ");
    r_sr_30min_pr=0; for i13  in ${r[@]}; do  r_sr_30min_pr=$(    bc <<< "scale=4; $r_sr_30min_pr+$i13/$size_f_m    ");   done;
    b_t_30min=0; for i in ${r[@]}; do  [[  $(    bc <<< "scale=2; $i>0    ")  -eq 1 ]]  &&   b_t_30min=$(    bc <<< "scale=4; $b_t_30min+100/$size_f_m    ");   done;   



    progress_bar


    printf  " r=%-20s |\n %.1f%% %s\n r_summa=%s ema5min=%s la5min=%s |  ema5min/r_summa=%s%% la5min/r_summa=%s%%  | r_sr_30min_pr=%-5.2f r_sr_30min_pr/r_summa=%s%%   \n\n"                               \
                                     " ${r[*]}"    \
                                     $( tr "." "," <<< "$b_t_30min" )   \
                                     "$b_t_30min_graph" \
                                     "$r_summa" \
                                      $( bc <<< "scale=2; ($la_now*12.5)/1" ) \
                                      $( bc <<< "scale=2; ($la_now)/1" ) \
                                      $( bc <<< "scale=2; 100*($la_now*12.5)/$r_summa" ) \
                                      $( bc <<< "scale=2; 100*($la_now)/$r_summa" ) \
                                      $( tr "." "," <<< "$r_sr_30min_pr" )  \
                                      $( bc <<< "scale=2; 100*($r_sr_30min_pr)/$r_summa" )  \
                                      | tr "," "." 







    la_p="$la_now"
    sleep 5


done;  
exit 0


###############################################################################
# конец
###############################################################################




