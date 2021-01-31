#!/bin/bash
# скрипт меняет местами слои в overlayFS

set -e

export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

# корневая папка где лежит бекенд overlay
root_folder=/mnt/overlay1

# подразумевается что структура бекенд папок overlay выглядит так
#
#               lowerdir=$root_fodler/lower,
#               upperdir=$root_folder/upper/upper,
#               workdir=$root_folder/upper/workdir
#               mergedir=$root_folder/merged
#
# и оверлей собирается вот так
#        sudo mount -t overlay -o \
#       $lowerdir, \
#       $upperdir, \
#       $workdir \
#       none /$merge_dir
#
# также продразумевается что вот эти папки являются точками монтирования
#       $root_folder/lower
#       $root_folder/upper
#






#  стопим smbd service
    service smbd stop
# проверяем что он остановился
if  [[ ($(service smbd status | grep 'Active: active' | wc -l)  ==  1 ) ]]
then
    echo "error! fail to stop smbd"; exit 1
fi


smb_point="$root_folder/merged"

# отмонтируем overlay
# если отмонтировать нечего то изначально чтото нетак и скрипт выдаст автомтом ошибку и прекратит дальнейшее исполнение
# потому вверху мы установили set -e

mergedir="$root_folder/merged"
mnt_point=$mergedir
    umount $mnt_point




# определяем LVM lv устройства отвечающие за lower и upper
# при этом предварительно проверяем что точка монтирования примонтирована
lowerdir="$root_folder/lower"
mnt_point=$lowerdir
if  [[ ($(df -h | grep "$mnt_point" | wc -l)  !=  0 ) ]]
then
    L1=$(df -h | grep "$mnt_point" | awk '{print $1}')
else
    echo "error! LVM backend for overlay lower is not mounted"; exit 1
fi

mnt_point="$root_folder/upper"
if  [[ ($(df -h | grep "$mnt_point" | wc -l)  !=  0 ) ]]
then
    U1=$(df -h | grep "$mnt_point"  | awk '{print $1}')
else
    echo "error! LVM backend for overlay lower is not mounted"; exit 1
fi

# это тоже надо отмонтировать
# два раза делаем umount потому что --bind заюзан при монтировании
mnt_point=$lowerdir
    umount $mnt_point
    umount $mnt_point


# аналогично
mnt_point="$root_folder/upper"
    umount $mnt_point


# форматируем бывший lower
mkfs.ext4 -F $L1 1>/dev/null 2>&1


# монтируем бывший lower теперь уже в upper
mount -o noatime,data=journal $L1 $root_folder/upper
chown nobody.nogroup $root_folder/upper
# создаем в нем подпапки $upperdir  $workdir
upperdir=$root_folder/upper/upper
workdir=$root_folder/upper/workdir
mkdir $upperdir $workdir

#монтируем бывший upper в lower
mnt_point=$lowerdir
mount -o noatime,data=journal $U1 $mnt_point
chown nobody.nogroup $mnt_point
     # если нет папки то создаем ее
    if [[ ! -d $mnt_point/upper ]]
    then
        mkdir $mnt_point/upper
    fi
mount -o noatime,data=journal --bind $mnt_point/upper $mnt_point
chown nobody.nogroup $mnt_point


# все готово. монтируем overlay
mount -t overlay -o noatime,lowerdir=$lowerdir,upperdir=$upperdir,workdir=$workdir  none $mergedir
chmod 777 $mergedir
chown nobody.nogroup $mergedir

# стартуем smb
service="smbd"
if [ -f "/etc/init.d/$service" ]; then
    service smbd start
fi


# далее нужно записать файл с settings который можно прочитать запустить после перезагрузки ОС и на основе него потом смонтировать overlay раздел

# создаем папку под файл настроек
     # если нет папки то создаем ее
    settings_folder="/etc/pagecache"
    create_folder=$settings_folder
    if [[ ! -d $create_folder ]]
    then
        mkdir $create_folder
    fi

# пишем настройки в файл
# список переменных которые мы будем писать в файл настроек
#
#	upper_lvm_device=$L1
#	upper_folder=$root_folder/upper
#
#	lower_lvm_device=$U1
#	lower_folder1=$lowerdir
#	lower_folder2=$lowerdir/upper
#	lower_folder3= $lowerdir

#	lowerdir=$lowerdir
#	upperdir=$upperdir
#	workdir=$workdir
#	mergedir=$mergedir

    settings_file="$settings_folder/settings.ini"
    

echo	""					> $settings_file
echo	"# файл с переменными pagecache"	>> $settings_file
echo	""					>> $settings_file
echo	L1=\"$L1\"				>> $settings_file
echo	root_folder=\"$root_folder\"		>> $settings_file
echo	""					>> $settings_file
echo	U1=\"$U1\"				>> $settings_file
echo	lowerdir=\"$lowerdir\"			>> $settings_file
echo 	""					>> $settings_file
echo	upperdir=\"$upperdir\"			>> $settings_file
echo	workdir=\"$workdir\"			>> $settings_file
echo	mergedir=\"$mergedir\"			>> $settings_file










