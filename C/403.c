#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define SIZE 1024*1024*1024
#define TIME 300


int main() {
    // Создаем анонимную память
    void *ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS  , -1, 0);
    if (ptr == MAP_FAILED) {
        // Обработка ошибки
        return -1;
    }


// актвииурую THP (transparent huge pages)
memset(ptr, 0, SIZE);  // это обязатлеьно иначе не срабтает
if (madvise(ptr, SIZE, MADV_HUGEPAGE) != 0) {
    perror("madvise");
    munmap(ptr, SIZE);
    return -1;
}






    printf("старт блока %p \n", ptr);


    // читаем
	char data;
	    for (size_t i = 0;   i < SIZE;   i++) {  
    		data =  *(  (char*)ptr+i   )      ;


	    }


    // Используем ptr как указатель на выделенную память
    // Например, записываем данные в эту память
    memset(ptr, 0x10, SIZE/10);

    
    printf("сплю %i сек\n", TIME);
    sleep(TIME);

    // Освобождаем память после использования
    munmap(ptr, SIZE);

    return 0;
}


