#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(void) {


  printf ("pid = %i\n", getpid() );

  char const * ptr_path = "/tmp/1.txt";
  char const * ptr_mode = "r";
  FILE * i_stream = NULL;

  i_stream = fopen(ptr_path,  ptr_mode);

  sleep(30);
  fclose(i_stream);

 exit(0);

}
