#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


int main() {




 int (*p) [] = malloc(100);
 //printf ("p+1 = %p \n", p+1);
 int *b = *p;
 (*p)[1] = 0x10;
 free (p);

// printf("%i \n", sizeof(*p));

  int (*q)[10] = malloc (5);
  free (q);
  
 int vasya[10];
 printf("%i \n", sizeof(vasya));

 char cc[] = "123";
 printf ("%i   \n", sizeof(cc));

 int (*pp) [0];
 void *qq = malloc (12);
  pp = qq;
 printf ("%i   \n", sizeof(*pp));
  *(*pp + 2) = 0x10;
  (*pp)[1] = 0x20;
 free (qq);


  printf ("%i \n", sizeof(sa_family_t) );
  
  printf ("%i \n", sizeof(struct sockaddr) );


};




