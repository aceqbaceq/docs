#########################################################################
#           набросок как редактировать fstab                            #
#########################################################################
# далее нам надо отредактировать fstab
# нужно вычистить старые строчки lower и upper
# чтото типа такого
#       sed -i '/\/mnt\/overlay1\/lower/d' /etc/fstab
#       sed -i '/\/mnt\/overlay1\/upper/d' /etc/fstab
# итак удаляем из fstab старые строки lower  и upper
#       задаем путь к файлу
####file_path="/tmp/fstab"

# задаем паттерн который будет искать строки вида
#       /mnt/overlay1/lower
#       /mnt/overlay1/upper
####fstab_lower="$lowerdir"
####fstab_upper="$root_folder/upper"

# запускаем удаление строк по паттерну
# будет удалены все строки если их несколько
####    tmp=$fstab_lower
####    sed_tmp=$(echo "$tmp" | sed 's!\/!\\/!g')
####    sed -i '/'"$sed_tmp"'/d' $file_path

####    tmp=$fstab_upper
####    sed_tmp=$(echo "$tmp" | sed 's!\/!\\/!g')
####    sed -i '/'"$sed_tmp"'/d' $file_path


#теперь добавляем в fstab свежий upper
####    echo "$L1       $root_folder/upper      ext4    noatime,errors=remount-ro,data=journal  0       2"  >> /etc/fstab

#добавляем в fstab свежий lower
###mnt_point=$lowerdir
####    echo "$U1                       $mnt_point      ext4    noatime,errors=remount-ro,data=journal  0       2"  >> /etc/fstab
####    echo "$mnt_point/upper  $mnt_point      none    bind,noatime                    0       2"  >> /etc/fstab
################################################################################

