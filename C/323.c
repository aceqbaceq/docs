#include <stdio.h>


int func1(int **p);



int main(){


  int a    = 0x10;
  int *p   = &a;
  int **pp = &p;

  func1( pp  );
  

};



int func1(int **p){

    printf("привет из функции func1! **p = 0x%X \n", **p );
    return 0;
};



