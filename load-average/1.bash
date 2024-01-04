#!/bin/bash


# блок инициализации
k=13  # по скольким точкам усредняем
time=$((k*5))   # число промежутков времени
step=5    # длинна одного промежутка в секундах
e=$(awk -t '{print $1}' < /proc/loadavg)
t=0
t_array=();
p_array=();
LA_array=();
e_array=();



# препринт
printf "\nt-время\np-число R\D процессов\np_LA-реальный LA\nc_LA-расчетный LA \n\n"
printf "%3s | %4s | %5s | %5s | \n" "t" "p" "p_LA" "c_LA"      # p_LA реальный LA, c_LA расчетный LA
printf "%s\n" "----------------------------"




# основной блок вычислений
for i in $(seq $time)
  do 
    p=$(ps a -o stat | grep -E "R|D" | wc -l); p_array+=("$p")
    LA=$( awk -t '{print $1}' < /proc/loadavg | tr  -d "\n"); LA_array+=("$LA")
    [[ "$i" -gt 1 ]] &&  e=$( printf "%.2f" $( bc -l <<< "scale=2; $e*e(-5/60)+$p*(1-e(-5/60))" | tr "." "," ) | tr "," "." ); e_array+=("$e")

    printf "%3s | %4s | %5s | %5s | \n" "$t" "$p" "$LA" "$e"

    sleep "$step"
    t_array+=($t); let t+=("$step")
 done




# вычисление среднего арифетического
a_array=() # среднее арифметическое число процессов за одну минуту
for  (( c=0; c<"${#p_array[@]}"; c+="$k" )); do 
    a_sum=0

    for j in $(seq 0 1 "$(( k-1 ))"); do
	let a_sum=a_sum+"${p_array[c+j]}"
    done

    average=$( printf "%.2f" $( bc <<< "scale=2; $a_sum/$k" | tr "." "," ) | tr "," "." );

    for j in $(seq 0 1 "$(( k-1 ))"); do
        a_array+=($average)
    done

done




# вывод суммарной инфо на экран и в файл
printf "\n\nвывод суммарной инфо \n"
printf "\nt-время\np-число R\D процессов\np_LA-реальный LA\nc_LA-расчетный LA\na_array-среднее арифметическое \n\n"
printf "%3s | %4s | %5s | %5s | %8s |\n"     "t" "p" "p_LA" "c_LA" "a_array"      # p_LA реальный LA, c_LA расчетный LA a_a среднее арифметическое
printf "%s\n" "---------------------------------------"


[[ -f "./data" ]] && true > ./data
for  (( c=0; c<"${#p_array[*]}"; c++ )); do 
    printf "%3s | %4s | %5s | %5s | %8s | \n"      "${t_array[c]}" "${p_array[c]}"  "${LA_array[c]}" "${e_array[c]}" "${a_array[c]}"
    printf "%3s %4s %5s %5s %8s \n"      "${t_array[c]}" "${p_array[c]}"  "${LA_array[c]}" "${e_array[c]}" "${a_array[c]}" >>  ./data
done



