#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 1024*1024*1024
#define TIME 120


int main() {
    // Открываем /dev/zero
    int fd = open("/dev/zero", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }


    // Маппируем его в память
    void *p = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }






    char data;
    for (size_t i = 0;   i < SIZE;   i++) {  
         //*(  (char*)p+i   ) = 0x10;
          data = *(  (char*)p+i   );

    }




    // Маппируем его в память
    void *p2 = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p2 == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }






    for (size_t i = 0;   i < SIZE;   i++) {  
         //*(  (char*)p2+i   ) = 0x10;
          data = *(  (char*)p2+i   );

    }




    // пауза
    printf("пауза %i сек \n", TIME);
    sleep(TIME);


    // все закрываем
    munmap(p2, SIZE);
    munmap(p, SIZE);

    close(fd);



    return 0;
}


