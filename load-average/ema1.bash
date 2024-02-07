#!/bin/bash



#
#  инициализация
#
sample=5 # как часто идет сэмплирование

wixi_enable="1" ;   # использовать ли классическую формулу LA при расчете 
border_m="7" # указывает сколько первых минут надо считать по классической формуле (минимум обязательно хотя бы 7 минут)
la0="100" # если класическая формула дезактивиована то надо задать ema(-5с) чтобы можно было посчитать по итерационной формуле  ema(0) 
           # и все последующие ema(t), если ema(-5c)=la0 незадать то далее в тексте программы принимается что ema(0)=r(0)

read_inputfile_enable="1" # читать ли r(t) из файла
INPUT_FILE="./ema1.input" # файл с заготовленным r(t)
INPUT_FILE_ALLOWED_SIZE="$(( 20*60/$sample + 1))"

max_time="30" # если чтение r(t) из файла дезактировано задает для скольких минут рассчитывать r(t)

sma_enable="0" # считать ли среднее арифметическое SMA
print_screen="0" # печатать ли результаты на экране, значения  "1" или "0"
FN="./ema1-data.log" # куда выводить расчеты LA
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




#
# блок печати
#
printf "\n"
printf "p1=%.2f >> коэфициент LA(1min)                           \n" ""$( tr "." "," <<< $p1 )""
printf "p2=%.2f >> коэфициент LA(5min)                           \n" ""$( tr "." "," <<< $p2 )""
printf "p3=%.2f >> коэфициент LA(15min                           \n" ""$( tr "." "," <<< $p3 )""
printf "t  >>  время                                             \n"
printf "r  >>  число процессов R|D                               \n"
printf "ema >> расчет на основе всех членов последовтельности    \n"
printf "ema_it >> расчет на основе итерационной формулы          \n"
printf "la_p >> load average из практики                         \n"
[[ "$wixi_enable" -eq 1 ]] && printf  "активировано использование классической формулы\n" || printf "классическая формула дезактивирована \n"
[[ "$read_inputfile_enable" -eq 1 ]] && printf  "активировано чтение r(t) из файла \n" || printf "чтение r(t) из файла  дезактивировано \n"
printf "\n"




#
# функции
#

function wixi   {
    #
    # алгоритм расчета через формулу wi*xi
    # он нам нужен для того чтобы высчитать ema на первых 7 минутах работы функции
    #


    if [[  "$k" -le $(( $border_m*60/$sample   )) ]]; then

	local r=( ${v[@]:0:$(($k+1))} ); # echo "k=$k, r=${r[@]}"
	local r_last_index=$(( ${#r[*]}-1 )); # echo "r_last_index=$r_last_index"

	local p=$(  bc -l <<< "scale=11; e(-1/12)"  );  
	local summa_wixi=0; 
	local summa_wi=0;
	local j="0"


	#
	# summa(wi*xi)
	#
	for i in $(seq $r_last_index -1 0); do 
            
	    wi=$( bc <<< "scale=11; $p^$j"); #printf "j=%d wi=%.3f \n"    "$j"   
	    xi="${r[$i]}";  printf "%d %.3f \n"   "$(( i*5 ))"   $( tr "." "," <<< "$xi") | tr "," "."  >> "$FN"
	    summa_wixi=$(  bc <<< "scale=11; $summa_wixi+$wi*$xi"  ); 


	    let j=$j+1
	done; 


	#
	# summa(wi)
	#
	j=0
	for i in $(seq $r_last_index -1 0); do 

	    wi=$( bc <<< "scale=11; $p^$j"); 
	    summa_wi=$(  bc <<< "scale=11; $summa_wi+$wi"  ); 

	    let j=$j+1
	done; 
	# printf "\nsumma_wi=%.3f \n"   $( tr "." "," <<< "$summa_wi") | tr "," "."


	#
	# LA
	#
	LA_wixi=$(  bc <<< "scale=11; $summa_wixi/$summa_wi"  ); #  printf "\nt=%s LA_wixi=%.3f \n\n" "$t"   $( tr "." "," <<< "$LA_wixi") | tr "," "."
    fi

}




#
# данные r(t)
#

if [[ "read_inputfile_enable"  -ne "1" ]]; then 

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
    #v=( 10 1 1 1 1 1 1 1 1 1  1 1 1  1 )


    # два с три четверти  набор
    #v=()
    #v=( 17.7 23.6 22.7 24.1 18.6 17.1 23.3 22.8 26.4 23.9 26.8 28.0 28.4 30.2 29.5 25.2 24.3 24.7 23.5 20.5 18.6 21.8 24.2 25.0 27.2 24.3 26.5 20.6 21.0 19.1 18.6 16.4 17.2 16.6 19.0 19.2 15.4 19.7 23.7 )



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
    # седьмой набор данных 
    #


    v=(); tt="0"; pi="3.14159"; 
    time="$max_time"; # минуты
    last_index=$( bc <<< "$time*60/$sample " )

    	for tt in $(seq 0 1 "$last_index" ); do 
                       #tt=$(bc <<< "$jj+12*($j-1)")
    		   #summa_fr="$(shuf -i 0-3  -n 1)"
    		   summa_fr="0";   # беру элемент из массива а если его там нет то беру число 10

    # высокие частоты
    		   #summa_fr=$(  bc -l <<< "scale=2; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/(5/60))   "       ); # эту частоту  мы не используем
    		   #summa_fr=$(  bc -l <<< "scale=2; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/(10/60))  "       ); # эту частоту  мы не используем
    		   #summa_fr=$(  bc -l <<< "scale=2; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/(15/60))  "       ); # сдвиг фазы +0.0м| амплитуда   7%
    		   #summa_fr=$(  bc -l <<< "scale=2; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/(20/60))  "       ); # сдвиг фазы +0.0м| амплитуда   7%
    		   #summa_fr=$(  bc -l <<< "scale=2; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/(25/60))  "       ); # сдвиг фазы +0.0м| амплитуда  11%
    		   #summa_fr=$(  bc -l <<< "scale=2; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/(30/60))  "       ); # сдвиг фазы +9с| амплитуда 11%

    # низкие частоты
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +5*s((2*3.14)*$tt*(5/60)/1)  "      );  # сдвиг фазы +18c| амплитуда 26%
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/2)  "      );  # сдвиг фазы +22c| амплитуда 32%
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +4*s((2*3.14)*$tt*(5/60)/2.6)  "    );  # сдвиг фазы +27c| амплитуда 40%
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/4)  "      );  # сдвиг фазы +30с| амплитуда 64%
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +4*s((2*3.14)*$tt*(5/60)/5)  "      );  # сдвиг фазы +41с| амплитуда 65%
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +2*s((2*3.14)*$tt*(5/60)/6)  "      );  # сдвиг фазы +41с| амплитуда 65%

    		   #summa_fr=$(  bc -l <<< "scale=11; $summa_fr +10*s((2*3.14)*$tt*(5/60)/9) "      );  # сдвиг фазы +50с|  амплитуда 84%
    		   #summa_fr=$(  bc -l <<< "scale=11; $summa_fr +0.1*s((2*3.14)*$tt*(5/60)/10) "      );  # сдвиг фазы +51с|  амплитуда 85%
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +2*s((2*3.14)*$tt*(5/60)/15) "      );  # сдвиг фазы +1.0м| амплитуда 93%
    		   #summa_fr=$(  bc -l <<< "scale=11; $summa_fr +10*s((2*3.14)*$tt*(5/60)/20) "     );  # сдвиг фазы +1.0м| амплитуда 96%
    		   #summa_fr=$(  bc -l <<< "scale=11; $summa_fr +2*s((2*3.14)*($tt+0)*(5/60)/40) "  );  # сдвиг фазы +1 мин| амплитуда 99%
    		   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +4*s((2*3.14)*$tt*(5/60)/100)"      );  # сдвиг фазы +1 мин| амплитуда 99%
    		   #summa_fr=$(  bc -l <<< "scale=11; $summa_fr +1*s((2*3.14)*$tt*(5/60)/120)"      );  # 


    		    [[ $(bc <<< "$tt<=(7*60/$sample)") -eq 1 ]] &&  summa_fr=0
    		    #[[ $(bc <<< "$tt<(12*60/$sample)") -eq 1 ]]  &&  summa_fr=400
    		    [[ $(bc <<< "$tt>(7*60/$sample)") -eq 1 ]]  &&  summa_fr=$(  bc -l <<< "scale=11; $summa_fr +7" )

 		    [[ $(bc <<< "$summa_fr < 0 ") -eq 1 ]] &&  summa_fr=0 




    # прямоульный импульс tau/T=0.5 руками
    base_T="18"
    : '
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/37)/$pi ) * s( ($tt*5) * ( 37*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/35)/$pi ) * s( ($tt*5) * ( 35*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/33)/$pi ) * s( ($tt*5) * ( 33*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/31)/$pi ) * s( ($tt*5) * ( 31*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/29)/$pi ) * s( ($tt*5) * ( 29*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/27)/$pi ) * s( ($tt*5) * ( 27*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/25)/$pi ) * s( ($tt*5) * ( 25*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/23)/$pi ) * s( ($tt*5) * ( 23*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/21)/$pi ) * s( ($tt*5) * ( 21*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/9.5)/$pi ) * s( ($tt*5) * ( 19*(2*$pi)/(60*$base_T) ) )"      );  #  период
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/17)/$pi ) * s( ($tt*5) * ( 17*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/15)/$pi ) * s( ($tt*5) * ( 15*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/13)/$pi ) * s( ($tt*5) * ( 13*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/11)/$pi ) * s( ($tt*5) * ( 11*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/9)/$pi )  * s( ($tt*5) * (  9*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/7)/$pi )  * s( ($tt*5) * (  7*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/5)/$pi )  * s( ($tt*5) * (  5*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/3)/$pi )  * s( ($tt*5) * (  3*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    	   summa_fr=$(  bc -l <<< "scale=11; $summa_fr +( 4*(1/1)/$pi )  * s( ($tt*5) * (  1*(2*$pi)/(60*$base_T) ) )"      );  #  период 
    '

    : '
    # прямоугольный импульс tau/T=0.5 через цикл

    base_T=18
    for h_n in $(seq 1 2 30); do
        summa_fr=$(    bc -l <<< "scale=11; $summa_fr +(   (4/($h_n*$pi)) * s( ($tt*5) * (  $h_n*(2*$pi)/(60*$base_T) ) ) )"    );  #  период 
    done
    '



    # прямоульный импульс симетричный относиельно оси Y
    : '
    base_T=10
    tau=9
    amplituda=1
    for h_n in $(seq 1 1 30); do
        summa_fr=$(    bc -l <<< " \
                                    scale=11; $summa_fr +(  \
                                                             (2*$amplituda/($h_n*$pi)) * \
                                                             s( $h_n * 2*$pi/(60*$base_T) * (60*$tau) * 0.5 ) * \
                                                             c( ($tt*5) * (  $h_n*(2*$pi)/(60*$base_T) ) ) \
                                                         ) \
                                 "  \
                  );  #  период 

    done
    summa_fr=$(    bc -l <<< " \
                                    scale=11; $summa_fr +(  \
                                                             $amplituda*$tau/$base_T \
                                                         ) \
                             "  \
               );

    #
    '


    : '
    #
    # некоторый сигнал
    #
    base_T=10
    tau=9
    amplituda=1

    for h_n in $(seq 1 1 30); do
        summa_fr=$(    bc -l <<< " \
                                    scale=11; $summa_fr -(  \
                                                             (2*$amplituda/($h_n*$pi)) * \
                                                             s( $h_n * 2*$pi/(60*$base_T) * (60*$tau) * 0.5 ) * \
                                                             c( ($tt*5) * (  $h_n*(2*$pi)/(60*$base_T) ) ) \
                                                         ) \
                                 "  \
                  );  #  период 

    done
    '







    #		   [[  $( bc <<< "$summa_fr < 0" ) -eq  1  ]] && summa_fr="0"

    	           v+=(  "$summa_fr"   )
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



else
    # читаем r(t) из файла 
    [[  ! -f "$INPUT_FILE"   ]] && { echo "ERROR: Ты задал чтобы r(t) прочитать из файла $INPUT_FILE, но его несуществует."; exit 1; }
    INPUT_FILE_SIZE=$(wc -l < "$INPUT_FILE"); [[ "$INPUT_FILE_SIZE"  -gt "$INPUT_FILE_ALLOWED_SIZE"   ]] &&  \
                                                 { echo "Число строк  $INPUT_FILE_SIZE файле \"$INPUT_FILE\" больше чем разрешенное, урезаю размер чтения до $INPUT_FILE_ALLOWED_SIZE строк"; \
                                                   INPUT_FILE_SIZE="$INPUT_FILE_ALLOWED_SIZE"; \
                                                 };
    for i in $(seq "$INPUT_FILE_SIZE"); do  
        #(( "$i" & 1  )) && printf "Читаю данные из файла ..\r" || printf "Читаю данные из файла ...\r"
	printf "Читаю данные из файла ...$i/$INPUT_FILE_SIZE\r"
	str_temp="$(head  -n +"$i" < $INPUT_FILE | tail -n1)"
	p="$(  awk '{print $2}' <<< $str_temp  )";  v+=("$p")     # число процессов
	#t="$(  awk '{print $1}' <<< $str_temp  )";  t_array+=("$t")     # время t
    done
    echo -e "\nДанные из файла прочитаны.\n"
    #echo "v=${v[@]}, t=${t_array[@]}"; exit 1


fi  # конец этого  if [[ "read_inputfile_enable"  -ne "1" ]]












#
# вычисления
#



# 
# алогритм расчета EMA
#
n="${#v[*]}"; # размер массива 
              # при этом сука надо помнить что последний элемент в массиве он на -1 меньше!
for ((  k=0; k<"$((n))"; k++ ));  do


    # если актиирован расчет LA с использованием класической формулы то юзается этот блок if then
    if [[ "$wixi_enable" -eq "1"  ]]; then


            if [[  "$k" -le  $(( $border_m*60/$sample   )) ]]; 
            then
               echo -ne "Высчитываю LA на основе классической формулы для первых $border_m минут  $k/$(( $border_m*60/$sample )) 0->->->$(( $border_m*60/$sample ))\r"; 
        	wixi; ema_1min_array+=("$LA_wixi")



            else
                [[  "$k" -eq  $(( $border_m*60/$sample +1  )) ]] && echo "" || echo -en "Высчитываю LA на основе итеративной формулы для остального времени $k/$(( $n-1 )) $(( $border_m*60/$sample +1))->->->$(( $n-1 ))  \r"

        	ema_it=$( bc <<< "scale=11; $p1*${ema_1min_array[-1]}+(1-$p1)*${v[k]}" );  ema_1min_array+=("$ema_it") ; # echo "t=$t LA_it=$ema_it"

        	#
        	# печать на экране
        	#
        	: '
        	    [[  (  "$k" -eq  0 ||  $(( ($k-1) % 12 )) -eq 0   )&&(  ! "$k"  -eq 1 ) ]] &&  printf "%-6s| %-6s | %-6s | %-6s |  %-6s  | %-8s | %-9s |\n"  "t"      "r"   "ema"  "ema_it"  "la_p"  "ema_5min"  "ema_15min"
        	    printf "%-6s| %-6s | %-6.2f | %-6.2f |  %-6s  | %-8.2f | %-9.2f |\n"  "$t"   "${v[$k]}"   "$( tr "." "," <<< $ema )"   "$( tr "." "," <<< $ema_it )"             "$( [[ -n "$la_p"  && "$(( k ))" -lt ${#la_p[*]}    ]] && echo ${la_p[$((k+1))]} || echo 'undef' )"  "$( tr "." "," <<< $ema_5min )"  "$( tr "." "," <<< $ema_15min )"   | tr "," "."
        	    [[ "$k" -gt  0   &&  $(( ("$k") %  12 )) -eq 0  ]] &&  { printf  "^минута %s\n------\n"   "$(( k/12 ))"; }
        	'
            fi


    else 

                # здесь я рассуждаю так. если la0 незадан  тоесть незадан ema в точке t=-5с то тогда я считаю что 
                # ema(0)=r(0) основываясь на классической формуле
        	if [[ "$k" -eq 0  ]]; then
                      [[ -z "$la0" ]] && echo "WARNING: классическая формула дезактивирована. ema(-5с) незадан. принимаю ema(0)=r(0)" || echo "NOTICE: классическая формула дезактивирована. ema(-5с) задан и равен $la0" 
                      ema_it="${la0:-${v[0]}}" 
                else  
                     ema_it=$( bc <<< "scale=11; $p1*${ema_1min_array[-1]}+(1-$p1)*${v[k]}" );  
                fi
                echo -en "Высчитываю LA на основе итеративной формулы для всего времени $k/$(( $n-1 )) 0->->->$(( $n-1 ))  \r";
                ema_1min_array+=("$ema_it") ; # echo "t=$t LA_it=$ema_it"




    fi # конец [[ "$wixi_enable" -eq "1"  ]]




    let t+=5; t_array+=("$t")




done



echo ""


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
if [[ "$sma_enable" -eq 1 ]]; then
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


else

    for  (( c="0"; c<"${#v[@]}"; c++ )); do 
	# средне за  1 миунуту
	mean_1min_array+=("0")

	# средне за  5 миунут
	mean_5min_array+=("0")

    done





fi # конец вот этого if [[ "$sma_enable" -eq 1 ]]




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
: '
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

'

    printf "%-6s %-6s %-6.3f      \n"  \
            "${t_array[$k]}"\
            "${v[$k]}"\
             $( tr "." ","<<<  ${ema_1min_array[$k]} )\
            | tr "," "."   >>  "$FN"





done



echo -e "\nГотово.\n"; spd-say "boom baby boom baby"
