#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {

    int fd = open("/dev/zero", O_RDONLY);
    if ( fd < 0 ){
       perror ("error open");
    };
    printf("открыл файл \n");
    sleep(20); 
    close(fd);
    printf("закрыл файл \n");
    sleep(20);
    return 0;
}




