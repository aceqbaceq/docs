#!/bin/bash

set -e


# параметры как мы будем монтировать overlay
#               lowerdir=/mnt/overlay1/lower,
#               upperdir=/mnt/overlay1/upper/upper,
#               workdir=/mnt/overlay1/upper/workdir
#               /mnt/overlay1/merged


root_mnt="/mnt/overlay1"

# если нет папки куда будем монтировать то создаем ее
mnt_1="$root_mnt/lower"
lvm="/dev/mapper/vg02-lvol0"
    mnt=$mnt_1
    if [[ ! -d $mnt ]]
    then
        mkdir $mnt
    fi

    # если точка монтироавния непримонтирована то монтируем ее
    # вначале проверяем на основе по пути к папке, если папки в таблице маунтов нет
    if  [[ ($(df -h | grep "$mnt" | wc -l)  ==  0 ) ]]
    then
        # тогда дополнительная проверка что lvm lo уже незанят,
        if [[ ($(df -h | grep "$lvm" | wc -l)  !=  0) ]]
        then
            # если он занят тогда выходим с ошибкой
            echo "error! LVM $lvm is already mounted in wrong folder"; exit 1
        fi
        # иначе монтируем
        mount -o defaults,noatime $lvm $mnt
        # если нет папки то создаем ее
        if [[ ! -d $mnt/upper ]]
        then
            mkdir $mnt/upper
        fi
        mount -o defaults,noatime --bind $mnt/upper $mnt
    fi


    # теперь когда есть папка и внее примонтировано устройство все готово чтобы обьявить lowerdir переменную
    lowerdir=$mnt

# если нет папки куда будем монтировать то создаем ее
lvm="/dev/mapper/vg02-lvol1"
mnt_2="$root_mnt/upper"
    mnt=$mnt_2
    if [[ ! -d $mnt ]]
    then
        mkdir $mnt
    fi

    # если точка монтироавния непримонтирована то монтируем ее
    # вначале проверяем на основе по пути к папке, если папки в таблице маунтов нет
    if  [[ ($(df -h | grep "$mnt" | wc -l)  ==  0 ) ]]
    then
        # тогда дополнительная проверка что lvm lo уже незанят,
        if [[ ($(df -h | grep "$lvm" | wc -l)  !=  0) ]]
        then
            # если он занят тогда выходим с ошибкой
            echo "error! LVM $lvm is already mounted in wrong folder"; exit 1
        fi
        # иначе монтируем
        mount -o noatime $lvm $mnt
    fi




    # если нет папки то создаем ее
    if [[ ! -d $mnt/upper ]]
    then
        mkdir $mnt/upper
    fi

    # теперь все готово чтобы обьявить upperdir переменную
    upperdir=$mnt/upper


    # если нет папки то создаем ее
    if [[ ! -d $mnt/workdir ]]
    then
        mkdir $mnt/workdir
    fi

    # все готово чтобы обьявить workdir переменную
    workdir=$mnt/workdir



mergedir=$root_mnt/merged
    mnt=$mergedir

    # если overlay уже примонтирован то немонтируем его. иначе монтируем
    if  [[ ( $(mount | grep "$mnt" | wc -l)  ==  0 ) ]]
    then
        mount -t overlay -o noatime,lowerdir=$lowerdir,upperdir=$upperdir,workdir=$workdir none $mergedir
    fi

