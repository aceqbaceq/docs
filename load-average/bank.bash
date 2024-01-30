#!/bin/bash




ema=1; ema_mujika="$ema"; ema_moe="$ema"; ema_linux="$ema"
tau=60
h=5
p_moe=$( bc -l<<<"scale=11;      ($tau-$h)/$tau     ")
p_mujika=$( bc -l<<<"scale=11;      ($tau)/($tau+$h)     ")
p_linux=$( bc -l<<<"scale=11;      e(-5/60)     ")


minutes=1
ema_initial="$ema"

for t in $(seq 0 $h $(( $minutes*60 )) ); do 

    [[ "$t" -gt 0  ]] && ema_moe=$( bc<<<"scale=11;      $ema_moe*$p_moe     ");
    [[ "$t" -gt 0  ]] && ema_mujika=$( bc<<<"scale=11;      $ema_mujika*$p_mujika     ");
    [[ "$t" -gt 0  ]] && ema_linux=$( bc<<<"scale=11;      $ema_linux*$p_linux     ");



    printf "%3d %.5f %.5f %.5f \n"     \
                                       "$t"\
                                        $( tr "." "," <<<  "$ema_moe" ) \
                                        $( tr "." "," <<<  "$ema_mujika" ) \
                                        $( tr "." "," <<<  "$ema_linux" ) \
                                        | tr "," ".";



done

etalon=$(bc -l <<< "scale=11;     $ema_initial*e(-1)" )  
oshibka_moe=$(bc -l <<< "scale=11;     100*($ema_moe-$etalon)/$etalon  ")
oshibka_mujika=$(bc -l <<< "scale=11;     100*($ema_mujika-$etalon)/$etalon  ")
oshibka_linux=$(bc -l <<< "scale=11;     100*($ema_linux-$etalon)/$etalon  ")



printf  "\n etalon  = %s \n\n oshibka_moe = %s%%\n oshibka_mujika = %s%%\n oshibka_linux = %s%% \n\n"   \
                                "$etalon" \
                                "$oshibka_moe" \
                                "$oshibka_mujika"  \
                                "$oshibka_linux"  \
                                 | tr "," "."



exit 1


: '
ema=0.16
p=$( bc -l<<<"scale=11;      e(-5/60)     ")
vklad=0
minutes=10
pred="$ema"

for t in $(seq 0 5 $(( $minutes*60 )) ); do 

    ema=$( bc<<<"scale=11;      $ema*$p+(1-$p)*$vklad     ");
    delta_t=$( bc<<<"scale=11;   ($pred - $ema) * 60"   |   tr "." ","   ); pred="$ema"

    
    printf "%3d %.3f  %.3f  %.1f  %.3f \n"     \
                                       "$(($t+5))"\
                                        $( tr "." "," <<<  "$ema" ) \
                                        $( bc<<<"scale=11;     $ema*60   " | tr "." "," ) \
                                        "$delta_t" \
                                        $( bc<<<"scale=11;  (60-4.8*($t/5+1))/(60+4.8*0.5*($t/5))" | tr "." "," )  \
                                        | tr "," ".";


done

'





: '
ema=0
vklad=1
p=$( bc -l<<<"scale=11;      e(-5/60)     ")
minutes=5; step="4.797"; last_n=$( bc -l<<<"scale=0;    $minutes*60/$step +1      ")

for n in $(seq 0 1 $last_n); do 


     ema=$( bc<<<"scale=11;      $ema*$p+(1-$p)*$vklad     ");

    printf "%s %.3f \n"       $( bc<<< "scale=3; $n*$step" )             $( tr "." "," <<<  "$ema" )  | tr "." ","
done
'






: '

#
# для процесса b
#
FN="./bank-b.log"; [[ -f "$FN" ]] && true > "$FN"
b_array=( 1 1 1 1 1 1 1 1 1 1 1 1 1 ); #число рублей у процесса  или время  работы процесса по 5секунд

db=1 # вклад процесса в банк у рублях за раз
ema="0.0"  # число долларов этого процесса  в банке на момент t=-5c
t=0
vklad=0 # ежедневный вклад
p=$( bc -l<<<"scale=11;      e(-5/60)     ")
minutes="5"; sample=5; n_last=$(( $minutes*60/$sample  +1    )) 


echo "process b"
for n in $( seq 0 1 $n_last);do
    vklad="0"; [[ "${b_array[$n]:-0}" -ne 0 ]] && let vklad=$vklad+$db || let vklad=$vklad+"0"
    ema=$( bc<<<"scale=11;      $ema*$p+(1-$p)*$vklad     "); #echo "ema=$ema"

    printf  "t=%-3d   vklad=%d  ema=%.3f \n"     "$(( $n*5 ))"     "$vklad"     $( tr "." "," <<< "$ema" )  | tr "," "."
    printf  "%-3d   %d  %.3f \n"     "$(( $n*5 ))"   "$vklad"   $( tr "." "," <<< "$ema" )  | tr "," "."   >> "$FN"


    
done



#
# для процесса c
#
FN="./bank-c.log"; [[ -f "$FN" ]] && true > "$FN"
c_array=( 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 ); #число рублей у второго процесса  или время  работы процесса по 5секунд


db=1 # вклад процесса в банк у рублях за раз
ema="0.0"  # число долларов этого процесса  в банке на момент t=-5c
t=0
vklad=0 # ежедневный вклад
p=$( bc -l<<<"scale=11;      e(-5/60)     ")
minutes="5"; sample=5; n_last=$(( $minutes*60/$sample  +1    )) 


echo -e "\n\n  process c"
for n in $( seq 0 1 $n_last);do
    vklad="0"; [[ "${c_array[$n]:-0}" -ne 0 ]] && let vklad=$vklad+$db || let vklad=$vklad+"0"
    ema=$( bc<<<"scale=11;      $ema*$p+(1-$p)*$vklad     "); #echo "ema=$ema"

    printf  "t=%-3d   vklad=%d  ema=%.3f \n"     "$(( $n*5 ))"     "$vklad"     $( tr "." "," <<< "$ema" )  | tr "," "."
    printf  "%-3d   %d  %.3f \n"     "$(( $n*5 ))"   "$vklad"   $( tr "." "," <<< "$ema" )  | tr "," "."   >> "$FN"


    
done


#
# суммарный график процессов b и c
#
FN="./bank-bc.log"; [[ -f "$FN" ]] && true > "$FN"
bc_array=()
ema="0.0"  # число долларов этого процесса  в банке на момент t=-5c
t=0
vklad=0 # ежедневный вклад
p=$( bc -l<<<"scale=11;      e(-5/60)     ")
minutes="5"; sample=5; n_last=$(( $minutes*60/$sample  +1    )) 


echo -e "\n\n  process b+c"
for n in $( seq 0 1 $n_last);do
    vklad="0"; let vklad=$vklad+${b_array[$n]:-0}+${c_array[$n]:-0} || let vklad=$vklad+"0"
    ema=$( bc<<<"scale=11;      $ema*$p+(1-$p)*$vklad     "); #echo "ema=$ema"

    printf  "t=%-3d   vklad=%d  ema=%.3f \n"     "$(( $n*5 ))"     "$vklad"     $( tr "." "," <<< "$ema" )  | tr "," "."
    printf  "%-3d   %d  %.3f \n"     "$(( $n*5 ))"   "$vklad"   $( tr "." "," <<< "$ema" )  | tr "," "."   >> "$FN"


    
done






#
# gnuplot
#
gnuplot -p -c ./bank-gnuplot-3in1.plot
sleep 600

'

