#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>

int main()
{

void *m;
      int j = 60;
     while( 1 )
    {
           int i = 1;
           while( i > 0 )
         {
                m = malloc(1024*1024*300);
                memset(m,0,1024*1024*300);
//                sleep (1);
                free(m);

                i--;
          }

     j--;
    }

        return 0;
}


