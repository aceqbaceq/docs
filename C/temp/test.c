#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef union{
    int i;
    char c[4];
}t_t;

/* child */
int main(int ac, char *av[])
{
    t_t tv;

    memcpy(tv.c, av[0], sizeof(int));

    printf("child: ac=%d, av0: %d, av1: %s\n", ac, tv.i, av[1]);
    return 0;
}