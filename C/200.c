#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define _GNU_SOURCE
#define BLOCKSIZE 512
#define COUNT  32768

int main(void)
{






int fd;
mode_t mode = O_RDONLY|__O_DIRECT;
char *filename = "/dev/sda";
fd = openat(AT_FDCWD, filename, mode);
if (fd < 0) {
      perror("Creation error");
      exit (1);
}



void *pbuf;
posix_memalign(&pbuf, BLOCKSIZE, COUNT);

//char bufer[512];
//pbuf = &bufer;

size_t a;
a = COUNT;



ssize_t ret;
ret = read(fd, pbuf, a);
if (ret < 0) {
      perror("read  error");
      exit (1);
}


close (fd);
exit (0);



}




