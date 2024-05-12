#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {


  printf ("pid = %i\n", getpid() );

  int i1 = 0x31;
  fputc(i1,stdout);
  fputc(0x0a, stdout);



  char ch1[] = "vasya";
  char * const ptr_ch1 = ch1;
  fputs(ptr_ch1,stdout);
  fputc(0x0a, stdout);





 exit(0);

}



