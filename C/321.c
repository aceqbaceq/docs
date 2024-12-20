#include <stdio.h>


int main(int argc, char *argv[]) {

  if(argc != 2)
    {
    printf("\n Usage: %s <file/path> \n",argv[0]);
    return 1;
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++)
    {
    printf("argv[%d] = %s\n", i, argv[i]);
    }








    char buffer[128];
    size_t bytesRead;
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Чтение данных из файла с использованием fread
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        printf("Read %zu bytes: %.*s\n", bytesRead, (int)bytesRead, buffer);
    }

    if (ferror(file)) {
        perror("Error reading file");
    }


    fseek(file , 0x0A , SEEK_SET):

    // повторное Чтение данных из файла с использованием fread
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        printf("Read %zu bytes: %.*s\n", bytesRead, (int)bytesRead, buffer);
    }



    fclose(file);
    return 0;
}


