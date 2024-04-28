#include<stdlib.h>
#include<stdio.h>


int main(){


// обьявляем переменные
int b;
int* a_Ptr;

// обращаемся к переменным делаем присвоение
a_Ptr = (int*) 0x20000000000000;


const char*      ff = "122\n";
char* const      ss = "hello\n";
printf (ss);


int i = 1;
int const * i_Ptr = &i;
i++;




//b = *(a_Ptr);




return(0);
};


