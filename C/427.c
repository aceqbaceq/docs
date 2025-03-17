#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main (){

  char *p1="/tmp/2.txt";

  int fd = open(p1, O_WRONLY|O_TRUNC|O_CREAT, 0666);
  if ( fd < 0 ){
       perror ("open() error");
       return 1;
     }

  int fd2;
  char c[10];
  while(1){
     fd2 = read(0, &c, sizeof(c));
       if ( fd2 < 0 ){
           perror ("read() error");
           return 1;
           }
     write(fd, &c, fd2);

  }

  close (fd2);
  close (fd);


return 0;

}


