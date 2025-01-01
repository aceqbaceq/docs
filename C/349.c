#include <sys/eventfd.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    printf("sizeof uint64_t = %i \n", sizeof(uint64_t));

    int efd = eventfd(0, 0);  // Создание eventfd с начальным значением 0
    if (efd == -1) {
        perror("eventfd failed");
        return 1;
    }
    printf("Eventfd descriptor: %d\n", efd);
    printf("пауза 20с \n");
    sleep(20);
    


    uint64_t a = 0x1020304050607080;

    if ( write(efd, &a, sizeof(a)) < 0 ){
        perror ("write error");
    };
    printf("write to eventfd is SUCCESS, пауза 30с \n");
    sleep(30);

    

    uint64_t b = 0x0;
    if ( read(efd, &b, sizeof(b)) < 0 ){
        perror ("read error");
    };
    printf("read from eventfd is SUCCESS \n");

    printf(" b = 0x%llX \n", b);
    

    sleep(60); 
    close(efd);
    return 0;
}

