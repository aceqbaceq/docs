#include <stdio.h>


int func1(int **p);
int func2(int **q);


int main(){


  int a    = 0x10;
  int b    = 0x20;
  int c    = 0x30;
  printf (" adress a = %p , address b = %p, address c = %p \n", &a, &b, &c );
  int *p[3];
  p[0]   = &a;
  p[1]   = &b;
  p[2]   = &c;
  int **pp = &(p[0]);

  func1( pp  );
  func1( &(p[0]) );
  func1 ( p );

// перехожу к func2
   func2( p );
   
  
};



int func1(int **p){

    printf("привет из функции func1! **p = 0x%X \n", **p );
    return 0;
};


int func2(int **q){

    printf("привет из функции func2! \n" );
    printf("q = %p, читаем первые 4 байта на которые указывает мой поинтер = %p \n", q, *q );
    printf("q+1 = %p, читаем следущие 4 байта от адреса на который указыает мой поинтер  = %p \n", (q+1), *(q+1) );
    printf("q+2 = %p, читаем еще дальше следущие 4 байта от адреса на который указыает мой поинтер  = %p \n", (q+2), *(q+2) );


    return 0;
};




