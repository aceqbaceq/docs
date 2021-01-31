#!/bin/bash
## скрипт
## проверяет свободное место на оверлей разделе 
## и если оно ниже заданного % то вызывает переключение снэпшота

# что интересно размер свободного места на разделе merged показывается ровно такой какой на разделе upper
# поэтому свободное место на overlay можно смотреть либо по upper разделу либо по merged

export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

# пороговое значение в % свободного места 
# при котором мы будем переключаться на другой снэпшот
freespace_minimum=50

# папка точки монтирования с upper  разделом overlay
overlay_partition="/mnt/overlay1/merged"

# создаем файл для складирования логов
log_folder=/var/log/pagecache
log_file=$log_folder/pagecache.log
    # если нет папки то создаем ее
    folder=$log_folder
    if [[ ! -d $folder ]]
    then
        mkdir $folder
    fi

    # если нет файла то создаем. 
    if [ ! -f "$log_file" ]
    then
	touch "$log_file"
    fi
    # если файл есть и он больше 10MB то пересоздаем
    if  [ $(stat "$log_file" | grep "Size" | awk '{print $2}') -gt 10485760  ]
    then
        echo "" > "$log_file"
    fi




# сколько места сейчас осталось на upper разделе
 left=$((100 - $(df -h | grep "$overlay_partition" | awk '{print $5}' |  sed 's/%//')))

# если места осталось меньше чем  $freespace_minimum переключаем на другой снэпшот
if  [ $left -lt $freespace_minimum  ]
then

    # если размер лог-файла больше 10MB то пересоздаем
    if  [ "$(stat "$log_file" | grep "Size" | awk '{print $2}')" -gt "10485760"  ]
    then
        echo "" > "$log_file"
    fi

    echo "$(date) запускаю скрипт переключения снэпшота" >> "$log_file"
    /usr/local/bin/pagecache_switch_snapshots.sh

    if [ $? -eq 0 ]
    then
	echo "$(date) снэпшот успешно переключен"  >> "$log_file"
    else
	echo "$(date) снэпшот переключить неудалось" >> "$log_file"
    fi

fi




