#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h> // for the definition of errno



int main(void)
{


printf ("номер процесса = %d \n", getpid());

int flags = O_RDONLY;
char *pathname = "/home/vasya/temp/!28/kubernetes.txt";

int fd = open(pathname, flags);


if (fd < 0) {
      perror("Creation error");
      printf("An error occurred. errno set to %d\n", errno);
      exit(1);

}

int num=30;
void *buf;

while ( num<=30 ) {

    ssize_t rr = read(fd, buf, 1);
    int position = lseek(fd, 0, SEEK_CUR);
    printf ("позиция=%i, символ=%zd \n", position, rr );
    sleep (10);
}


close(fd);


exit (0);

}




