#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


int main() {




  struct struc5 {
    int a;
    char vasya[];
  };

  struct struc5  sa6;

  printf("размер sa6  = %i \n", sizeof(sa6));
  printf("адрес начала  sa6.a  = %p \n", &sa6.a   );
  printf("адрес начала  sa6.vasya  = %p \n", &sa6.vasya   );

  *(sa6.vasya) = 0x10;
  



};




