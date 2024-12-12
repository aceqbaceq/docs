#define _GNU_SOURCE
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <error.h> 
#include <stdlib.h>

int main(int argc, char *argv[])  {




    // проверяю что программы была запущена с 1 аргументом
        if(argc != 2)
    {
    printf("\n Usage: %s </path/to/file> \n",argv[0]);
    return (1);
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++)
    {
    printf("argv[%d] = %s\n", i, argv[i]);
    }




 
 // открываю файл  для записи в хвост
   int fd;
   if ( (fd = open(argv[1], O_APPEND|O_WRONLY|O_CREAT,0666))  < 0 ){ 
      perror ("ошибка открытия файла: ");
      }
     



	if ( dprintf (fd, "| vasya | \n") < 0 ) {
	    perror ("вознкла ошибка при записи :" );

       }




   close (fd);


    return 0;
}



