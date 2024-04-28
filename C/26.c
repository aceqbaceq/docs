#include <stdio.h>
#include<unistd.h> 
#include<stdint.h>

int main () {

   /* local variable definition */
   pid_t pid;
   pid = getpid();
   printf ("pid = %d\n",pid);

   int a = 10;
   /* while loop execution */
   while( a < 20 ) {
          sleep(10);
        }; 



   return 0;
}
