#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])  {




    // проверяю что программы была запущена с 1 аргументом
        if(argc != 2)
    {
    printf("\n Usage: %s </path/to/file> \n",argv[0]);
    return 1;
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++)
    {
    printf("argv[%d] = %s\n", i, argv[i]);
    }


    sleep(5);



    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Маппируем файл в память
    off_t length = lseek(fd, 0, SEEK_END);
    char *mapped = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return 1;
    }

    // Читаем данные через mmap
    //printf("First byte: %c\n", mapped[0]);


struct stat stats;
  fstat(fd, &stats);
  printf ("file SIZE = %i bytes, file block(512b each) = %i blocks \n", stats.st_size, stats.st_blocks);

int result = 0;
  int i;
  for (i = 0; i < stats.st_size; i++) {
    result = mapped[i];
  }


    // Закрываем файл и освобождаем память
    munmap(mapped, length);
    close(fd);

    return 0;
}


