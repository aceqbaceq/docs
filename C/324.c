#include <stdio.h>


int func1(int **p);



int main(){


  int a    = 0x10;
  int b    = 0x20;
  int c    = 0x30;
  int *p[3];
  p[0]   = &a;
  p[1]   = &b;
  p[2]   = &c;
  int **pp = &(p[0]);

  func1( pp  );
  func1( &(p[0]) );
  func1 ( p );


};



int func1(int **p){

    printf("привет из функции func1! **p = 0x%X \n", **p );
    return 0;
};



