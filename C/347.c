#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {

 // меняю рабочую папку
 if ( chdir ("/home/noroot/temp/nc") < 0 ){
      perror ("chdir error");
 };
 
 
 
 // открываю файл 
 int fd1 = open("./456.txt", O_RDONLY);  // применяю относиельный путь
  if ( fd1 < 0 ){
      perror ("open error");
      return 1;
 };

 // читаю из него
 char buff[4];
 ssize_t rr = read(fd1, &buff, sizeof(buff-1));
 if (rr < 0 ){
    perror ("read error");
    return 1;
 };

 // печатаю на экране
 buff[3] = 0x00;
 printf ("%s \n", &buff);

 // закрываю файл
 close (fd1);

 // зануляю buff
 void *p = memset(&buff, 0x00, sizeof(buff));
 if (p == NULL ){
   perror ("memset error");
 };
 
 
 // открываю файл немного по другому
 fd1 = openat(AT_FDCWD, "456.txt", O_RDONLY);
  if ( fd1 < 0 ){
      perror ("open error");
 };


 // читаю из него
 rr = read(fd1, &buff, sizeof(buff-1));
 if (rr < 0 ){
    perror ("read error");
    return 1;
 };

 // печатаю на экране
 buff[3] = 0x00;
 printf ("%s \n", &buff);


 close (fd1);



}