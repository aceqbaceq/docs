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

mode_t mask = umask (0);
//umask (mask);
//printf("umask = %o\n",mask);





int flags = O_CREAT|O_WRONLY|O_TRUNC;
char *pathname = "/tmp/109.txt";
mode_t mode=0655;

int fd = open(pathname, flags, mode);


if (fd < 0) {
      perror("Creation error");
      printf("An error occurred. errno set to %d\n", errno);
      exit(1);

}


int num = 1;

while ( num <=30 ) {

    dprintf (fd, "N1");
    int position = lseek (fd, 0, SEEK_CUR);
    printf ("символ=K%i, оффсет=%i \n", num, position);
    num++;
    sleep(10);

}



close(fd);

//if ((unlink(pathname)) != 0) {
//      perror("unlink error");
//      exit (1);
//}

exit (0);

}



