#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


typedef union{
    int i;
    char c[4];
}t_t;

/* parent */
int main(int ac, char *av[])
{
    t_t tv;

    tv.i = 12345;

    if(fork() == 0){
        execlp("./test.exe", tv.c, "abcd", (char *)0);
    };
    return 0;
}
