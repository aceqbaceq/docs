#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>


int main() {




  struct struc5 {
    int a;
    char vasya[];
  };

  struct struc5  *sa5 = malloc(sizeof(struct struc5) + 10);
    if (sa5 == NULL) {
        perror("malloc failed");
        return 1;
    }

    sa5->a = 42;
    memcpy(sa5->vasya, "Hello", 6);  // Заполняем массив данными



    // Расширяем область памяти, увеличиваем массив до 
    struct struc5 *new_sa5 = realloc(sa5, sizeof(struct struc5) + 20);
    if (new_sa5 == NULL) {
        perror("realloc failed");
        return 1;
    }



  printf("адрес начала  sa5  = %p \n",     sa5   );
  printf("адрес начала  new_sa5  = %p \n", new_sa5   );






};




