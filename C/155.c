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



unsigned int i=0;
while(argv[i]) {
  printf("argv: $%u=%s\n", i, argv[i]);
  i++;
};

printf ("----------\n");

i=0;
while(envp[i]) {
  printf("envp: $%u=%s\n", i, envp[i]);
  i++;
};

printf ("----------\n");



pid_t p;
p=getpid();
printf ("155.exe : pid=%u\n", p);


exit (0);



}





