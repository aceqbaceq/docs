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


// read COUNT bytes from /dev/zero

int fd;
mode_t mode = O_RDONLY;
char *filename = "/dev/zero";
fd = openat(AT_FDCWD, filename, mode);
if (fd < 0) {
      perror("Creation error");
      exit (1);
}



void *pbuf;
posix_memalign(&pbuf, BLOCKSIZE, COUNT);


size_t a;
a = COUNT;



ssize_t ret;
ret = read(fd, pbuf, a);
if (ret < 0) {
      perror("read  error");
      exit (1);
}


close (fd);


// write COUNT bytes to /dev/sda

int f = open("/dev/sda", O_WRONLY|__O_DIRECT);


ret = posix_fadvise (f, 0, COUNT, POSIX_FADV_RANDOM);
if (ret < 0)
        perror ("posix_fadvise");


ret = write(f, pbuf, COUNT);
if (ret < 0) {
      perror("write  error");
      exit (1);
}

close(f);
free(pbuf);
return 0;





}




