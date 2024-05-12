#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(void) {


  //printf ("pid = %i\n", getpid() );

  int a1 = 0x3435;
  unsigned char ch1 = (unsigned char) a1;
  printf ("%c\n", a1);
  fputc(a1, stdout);
  fputc(0x0a, stdout);
  fputc(ch1, stdout);
  fputc(0x0a, stdout);




  int c2 = 0x3132;
  fputc(c2, stdout);
  fputc(0x0a, stdout);


  /*
  char const * ptr_path = "/tmp/1.txt";
  char const * ptr_mode = "w";
  FILE * ptr_i_stream = NULL;
  ptr_i_stream = fopen(ptr_path,  ptr_mode);

  int ret_c = 0;
  int c1 = 0x31;
  ret_c = fputc(c1, ptr_i_stream);
  fclose(ptr_i_stream);

  char const s1[] = {  'v', 'v', 'v', 'v', 'v', 0x0a, 0x00     };
  char const * ptr_s1 = s1;
  ret_c = fputs(ptr_s1, stdout);
  */

 exit(0);

}


