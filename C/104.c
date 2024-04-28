#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(void)
{

mode_t mask = umask (0);
umask (mask);
printf("umask = %o\n",mask);





int flags = O_CREAT|O_WRONLY;
mode_t mode = 0666;
char *pathname = "/tmp/1.txt";


int fd = open(pathname, flags, mode);


if (fd < 0) {
      perror("Creation error");
      exit (1);
}

close (fd);
exit (0);

}



