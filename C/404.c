#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TIME 300
#define PAGE 4096
#define MAL_SIZE 20*PAGE

int main(){


     char *p = malloc( MAL_SIZE );
     if(p == NULL){
         printf("malloc error\n");
         return 1; };
         
     printf("адрес = %p \n", p);
     



  char data;
    for (size_t i = 0;   i < 10*PAGE;   i++) {  
        data =  *(p+i)      ;  


    }



      memset(p, 0x10, 20*PAGE);


      sleep(TIME);
      free(p);
      
      
      
      return 0;
}

