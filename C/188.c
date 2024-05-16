
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


char const f_path[] = "/tmp/1.txt";


int main()
{

    int fd = open(f_path, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    char c[15]="00000000000000";
    read(fd,c,5);

    sleep(90);

    int ret =close(fd);
    if (ret != 0)
    {
        perror("close");
        return 1;
    }

    return 0;
}


