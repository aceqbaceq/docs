#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(void) {

  printf ("pid = %i\n", getpid() );
  char const * ptr_path = "/tmp/1.txt";
  int i = open(ptr_path, O_CREAT, O_RDONLY);
  printf ("i = %i\n", i );
  sleep(30);
  close(i);

 exit(0);

}
