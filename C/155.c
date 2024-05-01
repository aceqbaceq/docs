#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[], char *envp[])
{



unsigned int i=1;
while(argv[i]) {
  printf("$%u=%s\n", i, argv[i]);
  //do something
  i++;
};


pid_t p;
p=getpid();
printf ("pid=%u\n", p);


exit (0);



}





