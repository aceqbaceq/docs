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

  struct struc5  *sa5 = malloc(sizeof(struct struc5) + 10);







  printf("размер sa5  = %i \n", sizeof(*sa5));
  printf("адрес начала  sa5->a  = %p \n",     &(sa5->a)   );
  printf("адрес начала  sa5->vasya  = %p \n", &(sa5->vasya)   );

  *(sa5->vasya) = 0x10;




};




