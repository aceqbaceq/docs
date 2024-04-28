#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close


  int  main(void)
       {
           int fd;
           struct termios tio2;

           fd = open("/dev/pts/16", O_RDONLY);
           ioctl(fd, TCGETS, &tio2);
           close (fd);
       }




