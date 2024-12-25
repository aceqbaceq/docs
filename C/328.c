#include <stdio.h>


int func2(unsigned short num, char **qq);


int main(){


  char a[10]   = "123456789" ;
  char b[4]    = "abc";
  char c[3]    = "FF";
  char *p[3];
  p[0]   = &(a[0]);
  p[1]   = &(b[0]);
  p[2]   = &(c[0]);
  char **pp = &(p[0]);
  unsigned short num = 3;

   func2( num, pp );


};





int func2( unsigned short num, char **qq ){

   for (unsigned short i = 0; i<num; i++ ) {
      printf("*(qq+%hhi)  = %s \n", i, *(qq+i) );
   }


    return 0;
};




