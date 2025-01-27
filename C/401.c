#define _GNU_SOURCE      
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define TIMEOUT 300
#define MEMFD_NAME "my_memfd_example"



int main() {
    const char *filename = "/home/noroot/VM/ub18/ub18.img";  // Имя файла для отображения

    // Открываем файл для чтения
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }

    // Получаем размер файла
    off_t filesize = lseek(fd, 0, SEEK_END);
    if (filesize == -1) {
        perror("Ошибка получения размера файла");
        close(fd);
        return 1;
    }

    // Отображаем файл в память
    char *mapped = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Ошибка отображения файла в память");
        close(fd);
        return 1;
    }



  volatile uint64_t data;  // Для предотвращения оптимизации компилятором
    for (size_t i = 0;   i < filesize/( 20 * sizeof(uint64_t) );   i++) {  // я читаю не весь файл а только его 10%
        data = ((uint64_t*)mapped)[i];  // Чтение 8 байт за раз

        
    }
    
    




    // Создаем мемори-объект с именем "my_memfd_example"
    int fd1 = memfd_create(MEMFD_NAME, MFD_ALLOW_SEALING);
    if (fd1 == -1) {
            perror("memfd_create");
        exit(EXIT_FAILURE);
    }

    // Устанавливаем размер файла, который будет отображен в память
    size_t mem_size = 1024*1024*1024; 
    if (ftruncate(fd1, mem_size) == -1) {
        perror("ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }



    // Отображаем файл в память с помощью mmap
    void *addr1 = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    if (addr1 == MAP_FAILED) {
        perror("mmap");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    memset(addr1, 0x10, mem_size); // Копируем строку в память

    



      
      
    printf ("sleep %i sec    \n", TIMEOUT);
    sleep(TIMEOUT);



    // Освобождаем отображение и закрываем файл
    munmap(mapped, filesize);
    close(fd);




    // Очистка: unmap и close
    if (munmap(addr1, mem_size) == -1) {
        perror("munmap");
    }




    return 0;
}

