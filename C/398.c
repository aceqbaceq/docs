#define _GNU_SOURCE      

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>



#define MEMFD_NAME "my_memfd_example"

int main() {
    // Создаем мемори-объект с именем "my_memfd_example"
    int fd = memfd_create(MEMFD_NAME, MFD_ALLOW_SEALING);
    if (fd == -1) {
            perror("memfd_create");
        exit(EXIT_FAILURE);
    }

    // Устанавливаем размер файла, который будет отображен в память
    size_t mem_size = 1024*1024*1024; 
    if (ftruncate(fd, mem_size) == -1) {
        perror("ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }



    // Отображаем файл в память с помощью mmap
    //void *addr = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    void *addr = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }



    printf("начинаю писать в ммап \n");
    memset(addr, 0x10, mem_size); // Копируем строку в память
    printf("закончил писать в ммап \n");



   printf("пауза 120с \n");
   sleep(120);


    // Очистка: unmap и close
    if (munmap(addr, mem_size) == -1) {
        perror("munmap");
    }



    close(fd);
    return 0;
}



