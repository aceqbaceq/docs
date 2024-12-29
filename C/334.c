#include <stdio.h>
#include <unistd.h>
#include <error.h>


int main(int argc, char **argv)  {


    // проверяю что программы была запущена с 1 аргументом
        if(argc != 2)
    {
    printf("\n Usage: %s </path/to/file> \n",argv[0]);
    return (1);
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
    }

 


    
    FILE *source, *destination;
    char buffer[10];

    // Открываем исходный файл для чтения
    source = fopen(argv[1], "r");
    if (source == NULL) {
        perror("Error opening source file");
        return 1;
    }


   for (int i=0; i<2; i++){     
	// Читаем из исходного файла и записываем в целевой
	char *ret = fgets(buffer, sizeof(buffer)-1, source);
	if (ret == NULL ) {
    	    perror("Error reading  file");
    	    return 1;
	}



	if (fputs(buffer, stdout) < 0 ) {
    	    perror("Error writing to stdout");
    	    return 1;

        }
    
	printf ("\n");
    }

    printf("я успешно считал несколько раз из файла!\n");


    sleep(60);
    // Закрываем файлы
    fclose(source);


   return 0;
}


