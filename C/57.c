#include <stdio.h>
#include <stdlib.h>
  
extern char **environ;
 
int main(int argc, const char *argv[], const char *envp[]) {
  printf("environ:  %p\n", environ);
  printf("envp:     %p\n", envp);
  setenv("MY_NEW_VAR", "new_value", 1);
  puts("--Added MY_NEW_VAR--");
  printf("environ:  %p\n", environ);
  printf("envp:     %p\n", envp);
  return 0;
}

