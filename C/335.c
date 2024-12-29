#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>


int main() {


  
  struct struc7 {
    char vasya[2];
    int b;
  } ;

  struct struc7 sa6;
  printf ("struc7 size = %i    \n", sizeof(sa6) );
  *((char*)(&sa6)+0) = 0x10;
  *((char*)(&sa6)+7) = 0x10;
  *((char*)(&sa6)+8) = 0x10;






};




