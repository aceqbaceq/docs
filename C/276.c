#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
    // Проверка, что программа была запущена с 1 аргументом
    if (argc != 2) {
        printf("\n Usage: %s </path/to/file> \n", argv[0]);
        return 1;
    }

    // Печатаем считанные аргументы
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    sleep(1);

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Получаем информацию о файле
    struct stat stats;
    if (fstat(fd, &stats) == -1) {
        perror("Error getting file stats");
        close(fd);
        return 1;
    }

    off_t length = stats.st_size;
    if (length == 0) {
        printf("File is empty.\n");
        close(fd);
        return 1;
    }
    printf ("file SIZE = %ji \n", (intmax_t) stats.st_size);

    // Маппируем файл в память
    char *mapped = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return 1;
    }

    // Читаем данные через mmap
    char  result = 0;
    off_t j;
    for (off_t i = 0; i < length; i += 1000) {
        result = mapped[i];  // Здесь ты просто читаешь байты файла
        j = i;
    }
    printf ("last offset = %ji \n", (intmax_t) j );

    // Закрываем файл и освобождаем память
    munmap(mapped, length);
    close(fd);

    return 0;
}

