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


printf ("номер процесса = %i \n", getpid());

mode_t mask = umask (111);
//umask (mask);
//printf("umask = %o\n",mask);





int flags = O_WRONLY;
char *pathname = "/tmp/113.txt";
mode_t mode=0655;

int fd = open(pathname, flags, mode);


if (fd < 0) {
      perror("Creation error");
      printf("An error occurred. errno set to %d\n", errno);
      exit(1);

}


int num = 1;
int offset=8;

while ( num <=1 ) {

    int position = lseek (fd,offset, SEEK_SET);
    int off_cur  = lseek (fd,offset, SEEK_SET);
    dprintf (fd, "O1");
    printf ("символ=O1, заказал оффсет=%i, получил офсет=%i \n", position, off_cur);
    num++;
    offset += 2;
    sleep(10);

}



close(fd);
exit (0);

}



