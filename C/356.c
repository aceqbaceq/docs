#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define TIMEOUT  60

int main(int argc, char **argv){

   // проверка числа аргументов
   if ( argc < 2 ){
       printf ("число аргументов меньше 1. \n");
       return 1;
   };


  // проверка длины  аргументов
  int len=0;
  char *q;
  for (int i=1; i<argc; i++){
      q = *(argv+i);
      while (*q){
        len++;
        q++;
      };
   };
   printf("len = %i \n", len);
   if ( len < 20) {
     printf("error : длина всех аргументов меньше 20 символов. \n");
     return 1;
    };



  // распечатка аргументов
  for (int i=0; i<argc; i++){
    printf("argv[%i] = %s \n", i, *(argv+i) );

  };

  // замена аргументов
   strcpy(*(argv+1), ": master process   ");




    printf("пауза %iс чтобы залезть в ps\n", TIMEOUT);
    sleep(TIMEOUT);

};

