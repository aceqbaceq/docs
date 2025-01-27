#!/usr/bin/bash

arr1=( "MemTotal:"
"MemAvailable:"  
"Cached:"  
"Active:"  
"Inactive:"  
"Active\(anon):"  
"Inactive\(anon):"  
"Active\(file):"  
"Inactive\(file):"  
"AnonPages:"  
"Mapped:" 
"Shmem:" 
"Committed_AS:" 
"AnonHugePages:"
"SwapFree:" 
"SUnreclaim:"
"KernelStack:"
"PageTables:" )


 

for i in "${arr1[@]}";
    do 
	echo "$i = " $( echo  "scale=2; " $(grep  -E "^$i" < /proc/meminfo | awk '{print $2}')  "/1024" | bc ) "MB"
    done


