#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>

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




    // открываю файл
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

  // получаю размер файла
  struct stat stats;
  fstat(fd, &stats);
  float size_MB, size2_MB;
  size_MB = stats.st_size /1024 /1024;
  size2_MB = (stats.st_blocks * 512) /1024 /1024;


  printf ("file SIZE = %ji bytes = %.2f MBytes, file block(512b each) = %i blocks = %.2f MBytes  \n",  (intmax_t) stats.st_size, size_MB, stats.st_blocks, size2_MB);
  printf ("file SIZE = %i bytes \n",  (int) stats.st_size);


    close(fd);

    return 0;
}


