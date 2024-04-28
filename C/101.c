#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(void)
{

int fd;
mode_t mode = O_WRONLY|O_CREAT|O_TRUNC;
char *filename = "/tmp/1.txt";
fd = openat(AT_FDCWD, filename, mode, 0666);
if (fd < 0) {
      perror("Creation error");
      exit (1);
}

close (fd);
exit (0);

}


