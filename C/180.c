
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 200


int main(void) {


    int fd = open( "/tmp/1.txt", O_CREAT, O_RDONLY);
       if (fd  == -1)
      {
        	perror("open()");
	        printf ("Error no is : %d\n", errno);
                printf("Error description is : %s\n",strerror(errno));
      }



    char ptr_buf[BUF_SIZE];
    memset(ptr_buf, 0x00, sizeof(ptr_buf));

    if (read(fd, ptr_buf, BUF_SIZE) == -1)
      {
        	perror("read()");
	        printf ("Error no is : %d\n", errno);
                printf("Error description is : %s\n",strerror(errno));
      }

    char const * ptr_buf2 = ptr_buf;
    fputs(ptr_buf2, stdout);
    fputc(0x0a,stdout);


    return 0;
}






