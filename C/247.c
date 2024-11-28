#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close



void main (void) {


   int fd = open("/tmp/1.txt", O_RDONLY);
   sleep (120);

}

