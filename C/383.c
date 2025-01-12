#include <stddef.h>
#include <stdio.h>


int main() {


  char a    = 0x10;
  char *p_a = &a;

  char b    = 0x20;
  char *p_b = &b;

  char *p_c = NULL;

  char *ar[3] = { p_a, p_b, p_c };


  int i = 0;
  while (ar[i] != NULL) {
    printf ("i = %i, ar[%i] = 0x%hhX \n",   i,i,*(ar[i]) );
    i++;

  }; //END while

  return 0;
};

