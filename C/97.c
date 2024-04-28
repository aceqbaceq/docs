

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main()
{
// Declaration of a file descriptor
int fd;

// Opening a file
fd = open("/root/sasikala/testing",O_CREAT|O_EXCL);
// If Open is failed
if ( fd < 0 ) {
        printf("Opening file : Failed\n");
        printf ("Error no is : %d\n", errno);
        printf("Error description is : %s\n",strerror(errno));
}
// If Open is success
else
        printf("Opening file : Success\n");


// print hello world
printf("Hello, World!\n");
}


