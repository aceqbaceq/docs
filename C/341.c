#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


int main() {




  struct struc7 {
    int b;
    char vasya[2];
  } ;

  struct struc7 sa6;
  
  printf ("struc7 size = %i    \n", sizeof(sa6) );

  char *p = sa6.vasya;
  *(p+3) = 0x10;

  printf("0x%hhX   \n", *(p+3)  );
  





};




