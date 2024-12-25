#include <stdio.h>



int main(){


  char a[10]    = "123456789";
  char b    = 0x20;
  char c    = 0x30;
  char *p[3];
  p[0]   = &(a[0]);
  p[1]   = &b;
  p[2]   = &c;
  char **q = &(p[0]);

  printf("%s \n", *(q+0));

};


