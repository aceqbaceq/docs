#include <stdio.h>
#include <errno.h> // for the definition of errno
#include <stdlib.h> // for exit()
int main(void)
{

    int i;

 for (i = 1; i < 3; ++i)
 {
    int c;
    c = getchar();
    putchar(c);
    printf ("\n");
    printf("feof =  %d\n",feof(stdin));
    printf("ferror=  %d\n",ferror(stdin));
 }
    exit (0);

}



 