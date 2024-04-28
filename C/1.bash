#!/bin/bash

sleep 1; 

echo -n "v"; 
sleep 1; 

echo -n  "a"; 
sleep 1; 

echo -n "s"; 
sleep 1; 

echo -n "y"; 
sleep 1; 

echo  -n "a"; 
sleep 1;

echo -n -e "\x0D"; 
sleep 2; 



echo -n "*"
sleep 1;

echo -n "*"
sleep 1;

echo -n -e  "\x0A"
sleep 1;


echo -n "!"
sleep 1;

echo -n -e  "\x0A"
sleep 1;

echo -n -e "\x00v\x00a\x00s\x00y\x00a"
sleep 1;


echo -n -e "\x0B"
sleep 1;

echo -n -e "!"
sleep 1;



echo -n -e "\x0B"
sleep 1;

echo -n -e "!"
sleep 1;


echo -n -e "\x0B"
sleep 1;

echo -n -e "!"
sleep 1;


echo -n -e "\x0B"
sleep 1;

echo -n -e "!"
sleep 1;


echo -n -e "\x0B"
sleep 1;

echo -n -e "!"
sleep 1;

while true;
do 
    echo -n -e "\x0B"
    echo -n -e "!"
    echo -n -e "\x0B"
    echo -n -e "!"
    echo -n -e "\x0B"
    echo -n -e "!"

    echo -n -e "\x08\x08\x08\x08"



done;



echo -n -e "\x0A"
sleep 1;

