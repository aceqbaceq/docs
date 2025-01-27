#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(){


     void *p = malloc( 1024 * 1024 * 1024 );
     if(p == NULL){
         printf("malloc error\n");
         return 1; };
         
     void *p2 = malloc( 1024 * 1024 * 1024 );
     if(p2 == NULL){
         printf("malloc error\n");
         return 1; };

      sleep(30);
      free(p2);
      sleep(30);
      free(p);
      
      
      
      return 0;
}

