#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>

int main()
{
        while(1)
        {
                void *m = malloc(1024*1024*1024*1);
                memset(m,0,1024*1024*1024*1);
                sleep(100);
        }
        return 0;
}

