#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main (void) {

printf("This process is %d\n", getpid());
printf("The real user ID is %d\n", getuid());
printf("The effective user ID is %d\n", geteuid());



exit (0);
}
