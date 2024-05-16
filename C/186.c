
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


char const f_path[] = "/tmp/6.txt";


int main()
{

    int fd = open(f_path, O_RDWR|O_CREAT|O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    int ret =close(fd);
    if (ret != 0)
    {
        perror("close");
        return 1;
    }

    printf ("start pause 30 sec\n");
    sleep (30);
    printf ("pause is over\n");

    ret = link ("/tmp/6.txt", "/tmp/7.txt");
    if (ret == -1)
    {
        perror("link");
        return 1;
    }


    return 0;
}


