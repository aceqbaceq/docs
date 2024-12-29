#define _POSIX_C_SOURCE  200809L
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>


int main() {

    //
    struct sockaddr s1;
    dprintf (1, "sockaddr SIZE = %hi \n", sizeof(s1) );
    dprintf (1, "sockaddr  sa_family SIZE = %hi \n", sizeof(s1.sa_family) );
    dprintf (1, "sockaddr  sa_data[] SIZE = %hi \n",  sizeof(s1.sa_data) );





  // задаем новый структ
  struct Person {
  int id;
  char name[10];
  };


  struct Person p1;   // создаю person1 под этим структом
  *(p1.name) = 1;
  p1.name[2] =2;



  char vasya[1];
  char petya[0];

  void *p;
  p = malloc (4);
  int *q;
  q = p;
  int a = 10;
  p = &a;
  
  char *r = malloc( 10 );
  r[0] = 0x10;
  r[1] = 0x20;
  *(r+2) = 0x30;
  



}





