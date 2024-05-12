#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {


  printf ("pid = %i\n", getpid() );


  char const * ptr_path = "/tmp/1.txt";
  char const * ptr_mode = "w";
  FILE * ptr_i_stream = NULL;
  ptr_i_stream = fopen(ptr_path,  ptr_mode);

  int ret_c = 0;
  char const s1[] = {  'v', 'v', 'v', 'v', 'v',  'a', 'a', 'a', 'a', 'a', 0x0a, 0x00     };
  char const * ptr_s1 = s1;
  ret_c = fputs(ptr_s1, ptr_i_stream);

  char ch1[100];
  memset(ch1, '0', sizeof(ch1));
  void * ptr_ch1 = ch1;
  size_t t1 = fread(ptr_ch1, 5, 1, ptr_i_stream);
  fclose(ptr_i_stream);

  
  

  //int fd = open (ptr_path,O_CREAT ,O_RDONLY );
  //close(fd);

 exit(0);

}



