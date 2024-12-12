#include <stdio.h>
#include <dirent.h>
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



    const char *dirpath = argv[1];  // Замените на путь к вашему каталогу
    DIR *dir = opendir(dirpath);  // Открываем каталог
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Name: %s\n", entry->d_name);  // Выводим имя каждого файла/каталога
    }

    closedir(dir);  // Закрываем каталог
    return 0;
}

