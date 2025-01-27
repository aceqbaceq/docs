#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define SIZE 4096*256


int main() {
    // Создаем анонимную разделяемую память
    void *ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        // Обработка ошибки
        return -1;
    }

    printf("старт блока %p \n", ptr);

    int d = fork();



    if (d>0){
    // читаем
	char data;
	    for (size_t i = 0;   i < SIZE/2;   i++) {  
    		data =  *(  (char*)ptr+i   )      ;


		}


    // Используем ptr как указатель на выделенную память
    // Например, записываем данные в эту память
    memset(ptr, 0x10, SIZE/4);

    }
    
    else {

	char data;
	    for (size_t i = 0;   i < SIZE/4;   i++) {  
    		data =  *(  (char*)ptr+i   )      ;


		}


    // Используем ptr как указатель на выделенную память
    // Например, записываем данные в эту память
    memset(ptr, 0x10, SIZE/8);
    
    
    
    }    
    


    sleep(330);

    // Освобождаем память после использования
    munmap(ptr, 4096);

    return 0;
}


