#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>



int main()
{

      pid_t pid = getpid();
      printf("pid = %u\n", pid);
      int t = 30;

   for(int w=0; w<t; w++)
   {

      printf( "---\n"  );      
      sleep(3);
   }



    int klava = 0;

    void * bufer;
    char k[1];
    bufer = &k;

    printf ( "void address = %p\n", bufer );

    size_t count;
    count = 1;

    read( klava, bufer, count);



   printf ( "ti vvel s klavi %c\n", *(char *) bufer );

   char * vasya;
   vasya = (char *) bufer;

   printf ( "ti vvel s klavi %c\n", *vasya );


   return EXIT_SUCCESS;
}


