#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>



int main()
{

      pid_t pid = getpid();
      printf("pid = %u\n", pid);

   while(1)
   {

      printf( "...\n"  );      
      sleep(3);
   }
   return EXIT_SUCCESS;
}

