
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define SLT 300

char const f_path[] = "/tmp";


int main()
{

    int fd = open(f_path, O_RDWR|__O_TMPFILE, 0666);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    char const buff[] = "123\n";
    write(fd, buff, sizeof(buff));
    int e = SLT;
    printf("sleep for %isec\n", e);
    sleep(e);

    int ret =close(fd);
    if (ret != 0)
    {
        perror("close");
        return 1;
    }


    return 0;
}


