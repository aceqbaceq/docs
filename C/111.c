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


printf ("номер процесса =%i \n", getpid() );


int flags = O_RDONLY;
char *pathname = "/home/vasya/temp/!28/1.txt";
int fd = open(pathname, flags);


if (fd < 0) {
      perror("Creation error");
      printf("An error occurred. errno set to %d\n", errno);
      exit(1);

}

printf ("номер дескриптора = %i \n", fd);

printf ("изначальный оффсет=%zd\n", lseek(fd,0,SEEK_CUR));
printf ("------------------------\n");

int num=0;
char buf;

while ( num<=5 ) {

    int offset = lseek(fd, num, SEEK_SET);
    ssize_t rr = read(fd, &buf, 1);
    printf ("читаю из файла: оффсет=%i, символ=%zd\n", offset, rr );
    num++;
    sleep (10);
}


close(fd);


exit (0);

}




