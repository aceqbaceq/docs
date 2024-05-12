#include <unistd.h>
#include <stdio.h>

void terminate_buf(char *buf, ssize_t len)
{
    if(len > 0) {
        buf[len-1] = '\0';
    } else {
        buf[0] = '\0';
    }
}

int main()
{
    ssize_t  r;
    void * buf[1024];

    while(1) {
        r = read(0, buf, 1024);
        terminate_buf(buf, r);
        printf("read %d bytes: %s\n", r, buf);
    }

    return 0;
}


       ssize_t read(int fd, void *buf, size_t count);
