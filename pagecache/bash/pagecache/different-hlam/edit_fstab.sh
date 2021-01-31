#!/bin/bash

file_path="/tmp/1.txt"
root_folder=/mnt/overlay1
    lower=$root_folder/lower
    upper=$root_folder/upper

#df -h | tee $file_path



    tmp=$lower
    sed_tmp=$(echo "$tmp" | sed 's!\/!\\/!g')
    sed -i '/'"$sed_tmp"'/d' $file_path


    tmp=$upper
    sed_tmp=$(echo "$tmp" | sed 's!\/!\\/!g')
    sed -i '/'"$sed_tmp"'/d' $file_path

