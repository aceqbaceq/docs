#!/bin/bash


#
# первый набор начальных данных
#

#v=( 7 22 19 9 18 2 17 12 21 19 6 3 19 17 24 21 13 9 10 10 8 18 11 21 18 27 25 13 22 7 14 21 9 15 16 19 28 9 21 21 10 7 24 21 6 16 6 12 10 7 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 )
#la_p=( 0.62 2.26 3.52 3.88 4.93 4.69 5.60 6.03 7.15 8.02 7.86 7.39 8.48 9.08 10.52 11.52 11.63 11.58 11.54 11.49 11.29 11.91 11.92 12.57 13.24 14.42 15.51 15.23 15.77 15.07 14.98 15.39 15.03 15.35 15.40 15.85 16.91 16.75 15.49 15.61 15.80 15.26 14.20 14.66 15.01 14.21 14.11 13.22 13.04 12.72 12.18 11.20 10.31 9.48 8.72 8.02 7.38 6.79 6.25 5.75 5.28 4.86 4.47 4.11 3.78 )



# второй набор данных

#v=()
#v=( 28800 0 0 0    0 0 0 0    0 0 0 0       0 0 0 0    0 0 0 0    0 0 0 0        0 0 0 0    0 0 0 0    0 0 0 0         0 0 0 0    0 0 0 0    0 0 0 0          0 0 0 0    0 0 0 0    0 0 0 0   0 )



# два с полв набор данных

#v=()
#v=( 2 1 1 5 7 4 1 5 6 6  4 1 1  )




#
# третий набор данных 
#
#v=()
#a1=( "1"  )
#for i  in "${a1[@]}"; do
#    for j in $(seq 1 1 $((5*12+1)) ); do
#	v+=( "$i" )
#    done
#done; 


#
# четвертый набор данных 
#
#v=()
#a1=( 1 0 2 5 6  1  0 0  12  3 4 1 0 1)
#b1=()
#for i in $(seq 1 1 1);do  
#    b1+=( ${a1[@]} ) 
#done
#for i  in "${b1[@]}"; do
#    for j in $(seq 1 1 12); do
#	v+=( "$i" )
#    done
#done





#
# шестой набор данных 
#

#v=()
#a1=( 1 1 1 1 1 6 1 6 1 1 ) 
#a1=( 1 1 1 1 1 1 1 1 1 1 ) 
#tt=( 0 0 0 2 0 3  0 -1 )
#delta=0
#for q in $(seq 1 1 1 ); do
#    for i in $(seq 0 1  $(( ${#a1[*]}-1 )) ); do
#        
#        delta=$(bc  <<< "scale=1; $delta+${tt[$i]}" );
#	for j in $(seq 1 1 $((1*12)) ); do  # одна минута
#	    l="${a1[$i]}"; tt_i="${tt[$i]}";
#	done
#
#    done
#done




#
# шестой набор данных 
#

v=(); tt="0"
	for j in $(seq 1 1 15); do 
	    ampl=( 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 ) # число элементов здесь должно быть такое же как max $j
		for jj in $(seq 0 1 12); do   
                   tt=$(bc <<< "$jj+13*($j-1)")
		   #summa_fr="$(shuf -i 0-3  -n 1)"
		   summa_fr=${ampl[$j-1]:-10};   # беру элемент из массива а если его там нет то беру число 10
# высокие частоты
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/(5/60))   "       ); # эту частоту  мы не используем
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/(10/60))  "       ); # эту частоту  мы не используем
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +40*s((2*3.14)*$tt*(5/60)/(15/60))  "       ); # сдвиг фазы +0.0м| амплитуда   7%
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +40*s((2*3.14)*$tt*(5/60)/(20/60))  "       ); # сдвиг фазы +0.0м| амплитуда   7%
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +40*s((2*3.14)*$tt*(5/60)/(25/60))  "       ); # сдвиг фазы +0.0м| амплитуда  11%
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +40*s((2*3.14)*$tt*(5/60)/(30/60))  "       ); # сдвиг фазы +9с| амплитуда 11%

# низкие частоты
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/1)  "      );  # сдвиг фазы +18c| амплитуда 26%
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/2)  "      );  # сдвиг фазы +30c | амплитуда 43%
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/4)  "      );  # сдвиг фазы +30c| амплитуда 64%
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/5)  "      );  # сдвиг фазы +1.0м|  амплитуда 70%
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/10) "      );  # сдвиг фазы +1.0м|  амплитуда 87%
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/15) "      );  # сдвиг фазы +1.0м| амплитуда 93%
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/20) "      );  # сдвиг фазы +1 мин| амплитуда 95%
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/40) "      );  # сдвиг фазы +1 мин| амплитуда 99%
		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +10*s((2*3.14)*$tt*(5/60)/100)"      );  # сдвиг фазы +1 мин| амплитуда 99%
#		   summa_fr=$(  bc -l <<< "scale=2; $summa_fr +1*s((2*3.14)*$tt*(5/60)/120)"      );  # 




#		   [[  $( bc <<< "$summa_fr < 0" ) -eq  1  ]] && summa_fr="0"

	           v+=(  "$summa_fr"   )
		done
	done
#echo "${v[*]}"













#
# восьмой  набор данных 
#
: '
v=()


	for j in $(seq 0 1 $((15*12)) ); do  
	    v+=( $(bc -l <<< "scale=3; 10+5*c((2*3.14)*$j*(5/60)/2)"))
	done
'


#
# девятый  набор данных 
#
: '
v=()

min="15"
	for j in $(seq 0 1 $(($min*12)) ); do  
	    v+=(     $(  bc -l <<< "scale=3; $(cat /dev/urandom  | tr -d -c  "0-16"  |  head -c 1) *   $(cat /dev/urandom  | tr -d -c  "0-16"  |  head -c 1)"     )           )
	done
'












#
#  инициализация
#
print_screen="0" # печатать ли результаты на экране, значения  "1" или "0"
FN="./ema2-data.log"
wixi=0 # использовать ли неитеративную формулу для расчета la, значения "1" или "0"
la0=$( [[ -n "$la_p" ]] && echo "${la_p[0]}" ||  echo "10" ); printf  "\n\nla0=$la0 \n\n"  # начальный la
ema_5min="$la0"
ema_15min="$la0"

mean_1min=13 # по скольким точка усредняем средее арифметическое за 1 минуту
mean_5min=61 # по скольким точка усредняем средее арифметическое за 5 минут
ema_1min_array=()  # массив LA(1min) вычисляемый итеративно
ema_5min_array=()  # массив LA(5min) вычисляемый итеративно
ema_5min_array=()  # массив LA(5min) вычисляемый итеративно

p1=$(bc -l <<< "scale=11;e(-5/(1*60))");  # LA(1min)
p2=$(bc -l <<< "scale=11;e(-5/(5*60))");  # LA(5min)
p3=$(bc -l <<< "scale=11;e(-5/(15*60))");  # LA(15min)
[[ -f "$FN" ]] && true > "$FN"
t="0" # время
t_array=(); t_array+=("$t")




printf "\n"
printf "||============================================================||\n"
printf "||                                                            ||\n"
printf "||   p1=%.2f >> коэфициент LA(1min)                           ||\n" ""$( tr "." "," <<< $p1 )""
printf "||   p2=%.2f >> коэфициент LA(5min)                           ||\n" ""$( tr "." "," <<< $p2 )""
printf "||   p3=%.2f >> коэфициент LA(15min                           ||\n" ""$( tr "." "," <<< $p3 )""
printf "||   t  >>  время                                             ||\n"
printf "||   r  >>  число процессов R|D                               ||\n"
printf "||   ema >> расчет на основе всех членов последовтельности    ||\n"
printf "||   ema_it >> расчет на основе итерационной формулы          ||\n"
printf "||   la_p >> load average из практики                         ||\n"
printf "||                                                            ||\n"
printf "||============================================================||\n"
printf "\n\n"










#
# алгоритм расчета через формулу wi*xi
#
#  чтобы расчет сработал нужно завести доп массив с кучей нулей слева иначе
#  расчет нихрена не сработает
#

if [[  "$wixi" -eq 1 ]]; then
    sum=0
    tr_array=(); for i in $(seq 1 1 300); do tr_array+=( "0" ); done; 
    tr_array+=( "${v[@]}" )
    tr_size="${#tr_array[*]}"; echo "tr_size=$tr_size";
    for ((  j=0; j<"$tr_size "; j++ ));  do 	
	temp=$( bc <<< "scale=11;  ( $p1^( $tr_size-($j+1)) ) * ${tr_array[j]}" )
    	sum=$(  bc <<< "scale=11; $sum+$temp" )
    done; echo "sum=$sum"

    d=$( bc <<< "scale=11; (1-$p1^($tr_size))/(1-$p1)" )
    echo "деноминатор d=$d"
    ema=$(  bc <<< "scale=11; $sum/$d" )
    printf  "ema=$ema \n\n\n\n"
else
    ema="0"
fi





# 
# алогритм расчета через итеративные формулы
#
n="${#v[*]}"; # размер массива 
              # при этом сука надо помнить что последний элемент в массиве он на -1 меньше!
for ((  k=0; k<"$((n))"; k++ ));  do

    [[ "$k" -eq 0  ]] && ema_it="$la0"    ; ema_it=$( bc <<< "scale=11; $p1*$ema_it+(1-$p1)*${v[k]}" );      ema_1min_array+=("$ema_it")
    [[ "$k" -eq 0  ]] && ema_5min="$la0"  ; ema_5min=$( bc <<< "scale=11;$p2*$ema_5min+(1-$p2)*${v[k]}" );   ema_5min_array+=("$ema_5min")
    [[ "$k" -eq 0  ]] && ema_15min="$la0" ; ema_15min=$( bc <<< "scale=11;$p3*$ema_15min+(1-$p3)*${v[k]}" ); ema_15min_array+=("$ema_15min")

: '
#
# печать на экране
#
    [[  (  "$k" -eq  0 ||  $(( ($k-1) % 12 )) -eq 0   )&&(  ! "$k"  -eq 1 ) ]] &&  printf "%-6s| %-6s | %-6s | %-6s |  %-6s  | %-8s | %-9s |\n"  "t"      "r"   "ema"  "ema_it"  "la_p"  "ema_5min"  "ema_15min"
    printf "%-6s| %-6s | %-6.2f | %-6.2f |  %-6s  | %-8.2f | %-9.2f |\n"  "$t"   "${v[$k]}"   "$( tr "." "," <<< $ema )"   "$( tr "." "," <<< $ema_it )"             "$( [[ -n "$la_p"  && "$(( k ))" -lt ${#la_p[*]}    ]] && echo ${la_p[$((k+1))]} || echo 'undef' )"  "$( tr "." "," <<< $ema_5min )"  "$( tr "." "," <<< $ema_15min )"   | tr "," "."
    [[ "$k" -gt  0   &&  $(( ("$k") %  12 )) -eq 0  ]] &&  { printf  "^минута %s\n------\n"   "$(( k/12 ))"; }
'


    let t+=5; t_array+=("$t")

done



# вычисление среднего арифетического
# высчитываем так:  для n-ый точки например t=60s
# берем последние 13 точек включая нашу t=60 
# тоесть t=0,1,2,3...60 
# между ними интервал 1 минута
# для этих точек высчыиавем сренднюю арифм
# и эту среднюю наносим в t=60
# поэтому первая точка среднего арифметического появится 
# на графике только начиная с t=60
# для точек которые раньше у нас просто нет 
# материала на котором можно было бы считать
#
# пример k=13
# t=60s это n=12
# значит надо просуммировать элементы 0 1 2 3 4 5 6 7 8 9 10 11 12
# тогда c=12
# $(( c-(k-1) )) = 0
# будет for j in $(seq 0 1 12)
#
#
#
mean_1min_array=() # среднее арифметическое число процессов за одну минуту
mean_5min_array=() # среднее арифметическое число процессов за 5 минут


for  (( c="0"; c<"${#v[@]}"; c++ )); do 

    # средне за  1 миунуту
    a_sum_1min=0
        if [[ "$c" -lt "$(( ($mean_1min-1) ))"   ]]; then 
        average_1min="undef"   # для t<60s мы не можем посчитать среднее арифм поэтому приравниеваем к  undef

        else 
	    for j in $( seq  "$(( $c-($mean_1min-1) ))"   1  "$c"  ); do
    		a_sum_1min=$( bc  <<< "$a_sum_1min+${v[$j]}" )
	    done

	    average_1min=$( printf "%.2f" $( bc <<< "scale=11; $a_sum_1min/$mean_1min" | tr "." "," ) | tr "," "." );
	fi

    mean_1min_array+=("$average_1min")


    # средне за  5 миунут
    a_sum_5min=0
        if [[ "$c" -lt "$(( ($mean_5min-1) ))"   ]]; then 
        average_5min="undef"   # для t<60s мы не можем посчитать среднее арифм поэтому приравниеваем к  undef

        else 
	    for j in $( seq  "$(( $c-($mean_5min-1) ))"   1  "$c"  ); do
    		a_sum_5min=$( bc  <<< "$a_sum_5min+${v[$j]}" )
	    done

	    average_5min=$( printf "%.2f" $( bc <<< "scale=11; $a_sum_5min/$mean_5min" | tr "." "," ) | tr "," "." );
	fi

    mean_5min_array+=("$average_5min")





done





# вывод суммарной инфо на экран и в файл
#printf "\n\nвывод суммарной инфо: \n\n"




[[ -f "$FN" ]] && true > $FN
for  (( k=0; k<"${#v[*]}"; k++ )); do 



#
# вывод на экран
#


if [[ "$print_screen" -eq 1  ]]; then

     [[  ( "$k" -eq 0  ||   $(( ("$k"-1) % 12 )) -eq 0 ) && ( ! "$k" -eq 1  )   ]]  &&  printf "%-6s| %-6s | %-6s | %-6s |  %-6s  | %-8s | %-9s | %-12s | %-12s |\n"\
			      "t"\
			      "r"\
			      "ema"\
			      "ema_it"\
			      "la_p"\
			      "ema_5min"\
			      "ema_15min"\
                              "r_mean_1min"\
                              "r_mean_5min"



    printf "%-6s| %-6s | %-6.2f | %-6.2f |  %-6s  | %-8.2f | %-9.2f | %-12s | %-12s |\n"  \
            "${t_array[$k]}"\
            "${v[$k]}"\
            "$( tr "." "," <<< $ema )"\
            "$( tr "." "," <<< ${ema_1min_array[$k]} )"\
            "$( [[ -n "$la_p"  && "$(( k+1 ))" -lt ${#la_p[*]}    ]] && echo ${la_p[$((k+1))]} || echo 'undef' )"\
            "$( tr "." "," <<< ${ema_5min_array[$k]} )"\
            "$( tr "." "," <<< ${ema_15min_array[$k]} )"\
            "$( tr "." "," <<< ${mean_1min_array[$k]} )"\
            "$( tr "." "," <<< ${mean_5min_array[$k]} )"\
            | tr "," "."


    [[ "$k" -gt  0   &&  $(( ("$k") %  12 )) -eq 0  ]] &&  { printf  "^минута %s\n------\n"   "$(( ($k+1)/12 ))"; }


fi



#
#  печать в файл
#
    printf "%-6s %-6s %-6.2f %-6.2f %-6s %-8.2f %-9.2f %-9s %-9s %-6.2f  \n"  \
            "${t_array[$k]}"\
            "${v[$k]}"\
            "$( tr "." "," <<< $ema )"\
             $( tr "." ","<<<  ${ema_1min_array[$k]} )\
            "$( [[ -n "$la_p"  && "$(( k+1 ))" -lt ${#la_p[*]}    ]] && echo ${la_p[$((k+1))]} || echo 'undef' )"\
            "$( tr "." "," <<< ${ema_5min_array[$k]} )"\
            "$( tr "." "," <<< ${ema_15min_array[$k]} )"\
            "$( tr "." "," <<< ${mean_1min_array[$k]} )"\
            "$( tr "." "," <<< ${mean_5min_array[$k]} )"\
             $(      tr "." ","<<<        $(  bc <<< "scale=2; (${ema_1min_array[$k]} - 0.08*${v[$k]}) / 0.92"   )        )\
            | tr "," "."   >>  "$FN"



done




