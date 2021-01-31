#!/bin/bash
set -e

# план:
# прочитать пременные
# проверить несмонтирована ли оверлей уже
# потушить smb
# смонтировать
# запустить smb

export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

## прочитать переменные
# 	по идее должны считаться вот такие переменные
#    L1="/dev/mapper/vg02-lvol0"
#    root_folder="/mnt/overlay1"
#
#    U1="/dev/mapper/vg02-lvol1"
#    lowerdir="/mnt/overlay1/lower"
#
#    upperdir="/mnt/overlay1/upper/upper"
#    workdir="/mnt/overlay1/upper/workdir"
#    mergedir="/mnt/overlay1/merged"


 settings_folder="/etc/pagecache"
 settings_file="$settings_folder/settings.ini"

    file_path=$settings_file
    if [[ ! -f $settings_file ]]
    then
	echo "error! settings file is absent"; exit 1
    else
        source $settings_file
    fi




##  проверка что оверлей несмонтирован
if  [[ ($(df -h | grep "$mergedir" | wc -l)  !=  0 ) ]]
then
    echo "error! overlay is already mounted"; exit 1
fi

## потушить smbd
service smbd stop



## монтируем
# 	монтируем upper
mount -o noatime,data=journal $L1 $root_folder/upper
chown nobody.nogroup $root_folder/upper

# 	монтируем lower
mnt_point=$lowerdir
mount -o noatime,data=journal $U1 $mnt_point
chown nobody.nogroup $mnt_point
mount -o noatime,data=journal --bind $mnt_point/upper $mnt_point
chown nobody.nogroup $mnt_point

# 	монтируем overlay
mount -t overlay -o noatime,lowerdir=$lowerdir,upperdir=$upperdir,workdir=$workdir  none $mergedir
chmod 777 $mergedir
chown nobody.nogroup $mergedir

## запустить smbd
service smbd restart



