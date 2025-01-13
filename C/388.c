#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv, char** envp){

    char success = 0x0;
    char *p_arg1;
    char *p1;


    if (argc !=2 ){
      printf("ОШИБКА: нужен ровно один аргумент\n");
      return 1;
    } else {
             p_arg1 = *(argv+1);
      };



    size_t len_arg1 = strlen(p_arg1);


    int len_b1 = len_arg1+1;
    char *b1 = malloc(len_b1);

    memcpy(b1, p_arg1, len_arg1);
    *(b1+(len_arg1) ) = '=';


    char *temp = malloc(len_b1);
    memset(temp,0x0, len_b1);


    int i=0;
    int j=0;
    int ret1;
    while( *(envp+i) != NULL ) {
    
        p1 = *(envp+i);
        strncpy(temp, p1, len_b1);


        if (strncmp(b1, temp, len_b1) == 0){
            success = 0x1;
            break;
                    } 
        else {
                memset(temp,0x0, len_b1);
                i++;

                    } 



                    }//END while;



      if (success == 0x1){
           printf("переменная '%s' найдена.\n%s\n",  argv[1], p1);
      } else {
           printf("переменная %s НЕ найдена \n", argv[1]);
      }
      



      char *p3 = getenv(argv[1]);
      if (p3 != NULL) {
          printf ("я нашел эту же переменную через getenv(), вот она %s=%s  \n",    argv[1], p3);
      }
      else {
          printf ("я НЕ нашел эту же переменную через getenv() \n");
      
      }




      free(b1);
      free(temp);
      return 0;
}

