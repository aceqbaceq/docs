#define _GNU_SOURCE
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sched.h> 


int variable, fd;

int do_something() {
   variable = 42;
   printf("The parent: the variable = %d\n", variable);
   _exit(0);
}

int main(int argc, char *argv[]) {
   void **child_stack;
   char tempch;

   variable = 9;
   child_stack = (void **) malloc(16384);
   printf("The parent: the variable = %d\n", variable);

   clone(do_something, child_stack, CLONE_VM|CLONE_FILES, NULL);
   sleep(60);

   printf("The parent: the variable is =  %d\n", variable);
   return 0;
}

