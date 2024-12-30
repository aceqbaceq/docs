#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


int main() {




  struct struc4 {
    int vasya5[10];
  };



  struct struc4 *p5 = malloc(sizeof(struct struc4) );
  int *p = p5->vasya5;
  *(p+199)=0x10;

 
  free(p5);
  




};




