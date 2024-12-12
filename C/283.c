#include <stdio.h>
#include <unistd.h>
#include <error.h>


int main(int argc, char *argv[])  {


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

 

    if ( chdir(argv[1]) <0 ) {
       perror( " не могу сменить рабочий каталог : ");
    }



    
    FILE *source, *destination;
    char buffer[256];

    // Открываем исходный файл для чтения
    source = fopen("source.txt", "r");
    if (source == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Открываем целевой файл для записи
    destination = fopen("destination.txt", "w");
    if (destination == NULL) {
        perror("Error opening destination file");
        fclose(source);
        return 1;
    }

    // Читаем из исходного файла и записываем в целевой
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, destination);
    }

    // Закрываем файлы
    fclose(source);
    fclose(destination);

    printf("File copied successfully.\n");

   return 0;
}


