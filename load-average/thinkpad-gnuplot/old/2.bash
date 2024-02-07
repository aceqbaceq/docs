#!/bin/bash

# иницаидилизация
max_D=20   # макс число D процессов генерируемых за один промежуток времени
max_R=10   # макс число R процессов ...
time=120    # число промежутков времени
step=10    # длинна промежутка времени


for i in $(seq "$time")
do

    # запуск D процессов
    unset i; i=$(shuf -i 0-"$max_D"  -n 1)  # число D процессов

    if [[ "$i" -gt 0 ]]; then
	for i in $(seq $i); do 
	    ./30.exe & 
	done
    fi


    # запуск R процессов
    unset i; i=$(shuf -i 0-"$max_R"  -n 1)  # число cpu спайков

    if [[ "$i" -gt 0 ]]; then
	for i in $(seq $i); do 
	    a=$(shuf -i 1-"$step"  -n 1)  # длинна спайка
	    stress --cpu 1 --timeout "$a" 1>/dev/null &
	done
    fi

    sleep ""$step
done
