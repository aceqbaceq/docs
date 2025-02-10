#include <stddef.h>
#include <sys/klog.h>
#include <stdio.h>
#define SYSLOG_ACTION_SIZE_BUFFER 10
#define SYSLOG_ACTION_SIZE_UNREAD 9
#define SYSLOG_ACTION_READ 2
#define SIZE 264000


int main() {


    int size = SIZE;
    char c[size];
    char *p = &c[0];

    int fd = klogctl(SYSLOG_ACTION_SIZE_BUFFER, NULL, 0);
    if (fd <0){
      printf ("ОШИБКА: нужны права root\n");
      return 1;
    }

    printf ("размер кернел ринг  = %i bytes\n", fd);


    fd = klogctl(SYSLOG_ACTION_SIZE_UNREAD, NULL, 0);
    if (fd <0){
      printf ("ОШИБКА: нужны права root\n");
      return 1;
    }

    printf ("сколько байт лежит в кернел ринге  = %i bytes\n", fd);
    if (fd == 0){
      printf ("в кернел ринг лежит 0 байт поэтому просто выходим\n");
      return 0;
    }



    printf("читаю данные из кернел ринга\n");
    fd = klogctl(SYSLOG_ACTION_READ, p, size);
    if (fd <0){
      printf ("ОШИБКА: нужны права root\n");
      return 1;
    }
    printf("данные из кернел ринга прочитаны успешно\n\n");

    printf (" %s \n", p);


    fd = klogctl(SYSLOG_ACTION_SIZE_UNREAD, NULL, 0);
    if (fd <0){
      printf ("ОШИБКА: нужны права root\n");
      return 1;
    }

    printf ("сколько байт лежит в кернел ринге  = %i bytes\n", fd);



return 0;
}


