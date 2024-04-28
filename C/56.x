#include<sys/types.h>
#include <stdio.h>
   
int main()
{
    printf("Size of dev_t   =  %ld \n", sizeof( dev_t ));
    printf("Size of char   =  %ld \n", sizeof( char ));
    printf("Size of mode_t   =  %ld \n", sizeof( mode_t ));

    return 0;
}
