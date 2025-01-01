#include <sys/sendfile.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int main() {

       int fd = open("/usr/share/nginx/html/index.html", O_RDONLY);
         if ( fd <0 ){
                perror ("open file error");
         };

       struct stat st1;
       int ret = fstat( fd, &st1);
         if ( ret <0 ){
                perror ("stat file error");
         };

       off_t f_size = st1.st_size;
       ssize_t ret2 = sendfile(1, fd, 0, f_size);
         if ( ret2 <0 ){
                perror ("sendfile  error");
         };
       
      close(fd);

}



