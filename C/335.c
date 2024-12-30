#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


int main() {


  
  struct struc7 {
    char vasya[2];
    int b;
  } ;

  struct struc7 sa6;
  printf ("struc7 size = %i    \n", sizeof(sa6) );
  *((char*)(&sa6)+0) = 0x10;
  *((char*)(&sa6)+7) = 0x10;
  //*((char*)(&sa6)+8) = 0x10;

  int a=10;
  int *p = &a;
  printf("адреса p=%p, p+1=%p, p+2=%p, p+3=%p \n",  p, p+1, p+2, p+3  );
  
  int vasya2[2];
  int (*p2)[2]=&vasya2;
  printf("адреса p2=%p  p2+1=%p  \n",  p2, p2+1  );
  int i = (int)(p2+1) - (int)(p2);
  printf("адреса размер массива = %i  \n",  i  );
  
  
  int vasya3[2];
  int *p3  = vasya3;
   *(p+0) = 0x10;
   *(p+1) = 0x20;
  // *(p+2) = 0x30;
  //sleep(10);
  
  
  //int k2[10];
  //int (*pk2)[10] = &k2;
  //*(pk2) = 10;
  
  
  //int (*p4)[10] = &(int vasya4[10]);
  
  struct struc4 {
    int vasya5[10];
  };
  
    
  struct struc4 *p5 = malloc(sizeof(struct struc4) );
  //*(p5+1)=10;
  
  
  





};




