
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define m 131072



int main(int argc, char *argv[])
{

    if (argc != 2)
    {
      printf ("usage %s ./file_name  \n", argv[0]);
      exit(1);
    }



    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
      printf ("ERROR:open \n");
      exit(2);
    }



    char ptr_buf[m];
    memset(ptr_buf, 0x00, m);



    ssize_t rc = 1;
    while ( (rc = read(fd, ptr_buf, m-1)) != 0 )
    {
         //fputs(ptr_buf, stdout);
         //putc(0x0a, stdout);

    }



    if ( close(fd) == -1)
    {
      printf ("ERROR:close \n");
      exit(3);
    }




    return 0;
}






