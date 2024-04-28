#include <stdio.h>
#include<unistd.h> 


int main () {

   /* local variable definition */
   pid_t pid;
   pid = getpid();
   printf ("pid = %d\n",pid);

   int a = 10;
   /* while loop execution */
   while( a < 20 ) {
   }

   return 0;
}
