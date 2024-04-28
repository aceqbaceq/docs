#include <stdio.h>
#include <errno.h> // for the definition of errno
#include <stdlib.h> // for exit()
int main(void)
{
    int c;
    while ((c = getchar()) != EOF)
       putchar(c);

   printf ("мы словили EOF!\n");

    if (feof(stdin)) {
        printf("feof = %d\n", feof(stdin));
        exit(0);
    }
    else if (ferror(stdin)) {
        printf("An error occurred. errno set to %d\n", errno);
        perror("Human readable explanation");
        exit(1);
    }
    else {
        printf("This should never happen...\n");
        exit('?');
    }
}
