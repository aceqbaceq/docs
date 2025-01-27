#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "/usr/lib/libc.so.6";
    int fd;
    struct stat st;
    void *map;

    // Получаем информацию о файле, чтобы узнать его размер
    if (stat(filename, &st) == -1) {
        perror("stat");
        exit(1);
    }
    
    // Повторить 100 раз
    for (int i = 0; i < 100; i++) {
        // Открыть файл
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(1);
        }

        // Маппим файл в память с правильным размером
        map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (map == MAP_FAILED) {
            perror("mmap");
            close(fd);
            exit(1);
        }

        // Просто читаем первые несколько байт, чтобы убедиться, что маппинг произошел
        // Это можно пропустить, если не нужно фактически читать данные
        volatile char *ptr = map;
        for (int j = 0; j < 10; j++) {
            volatile char c = ptr[j];
        }


    }

    sleep(120);

    return 0;
}


