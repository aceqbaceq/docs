#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>

int main()
{
        while(1)
        {

         int inc=1024*1024*1024*1;
         void *p=(int*) calloc(1,inc);
         sleep(1);
    //     free(p);
        }
        return 0;
}

