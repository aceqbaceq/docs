#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define _POSIX_C_SOURCE 200809L


#define _GNU_SOURCE
#define BLOCKSIZE 512
#define COUNT  1





int main(void)
{


int fd;
mode_t mode = O_WRONLY;
char *filename = "/home/noroot/temp/nc/fifo1";
fd = open(filename, mode);
if (fd < 0) {
      perror("Creation error");
      exit (1);
}




ssize_t ret;
void *pbuf;
char bufer[10]="123456789";
pbuf = &bufer;
ret = write(fd,pbuf,10);

//ret = dprintf(fd, "vasssya\n");
if (ret < 0) {
      perror("read  error");
      exit (1);
}


//sleep(60);

close (fd);

close(fd);
return (0);





}




