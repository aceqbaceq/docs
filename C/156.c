#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{

int i=0;
while(envp[i]) {
  printf("%s\n", envp[i]);
  //do something
  i++;
};


exit (0);



}





