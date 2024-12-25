#include <stdio.h>


int func2(char **qq);


int main(){


  char a[10]   = "123456789" ;
  char b[4]    = "abc";
  char c[3]    = "FF";
  char *p[3];
  p[0]   = &(a[0]);
  p[1]   = &(b[0]);
  p[2]   = &(c[0]);
  char **pp = &(p[0]);

   func2( pp );
   
  
};





int func2(char **qq){

    printf("*(qq+0)  = %s \n", *(qq+0) );
    printf("*(qq+1)  = %s \n", *(qq+1) );
    printf("*(qq+2)  = %s \n", *(qq+2) );


    return 0;
};




