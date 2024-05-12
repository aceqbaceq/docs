
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define m 131072



int main(int argc, char *argv[])
{




   sleep(60);
   void * ptr_p = NULL;
   size_t s = 1024;
   ptr_p = malloc(s);
   sleep(60);
   free(ptr_p);


   sleep (60);
   s = 1 * 1024 * 1024;
   ptr_p = malloc(s);
   sleep(60);
   free(ptr_p);



   sleep(90);

    return 0;
}






