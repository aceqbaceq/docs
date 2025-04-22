#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Открываем файл
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Получаем размер файла
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t filesize = sb.st_size;
    if (filesize == 0) {
        fprintf(stderr, "File is empty.\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Мапим файл в память
    char *mapped = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE|MAP_NORESERVE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }




    // Читаем половину файла и выводим в stdout
    size_t half = filesize / 2;
    write(STDOUT_FILENO, mapped, half);
    printf("\n");
    sleep(15);


    // Читаем вторую половину файла и выводим в stdout
    write(STDOUT_FILENO, mapped + half, filesize - half);
    printf("\n");


    printf("повторно читаем весь файл\n");
    write(STDOUT_FILENO, mapped, filesize);
    printf("\n");




    // Освобождаем ресурсы
    munmap(mapped, filesize);
    close(fd);

    return 0;
}

