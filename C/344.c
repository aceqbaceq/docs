#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {



    int s = socket(AF_INET, SOCK_STREAM, 0);  // создаем сокет

    struct sockaddr_in *addr = malloc( sizeof(struct sockaddr_in) );  // создаем поинтер на структ sockaddr_in
                                                                     // причем мы не только поинтер создаем но и 
                                                                     // создаем тело в памяти на который указывает поинтер
    addr->sin_family = AF_INET;   // вбиваем в него параметры
    addr->sin_port = htons(6789);
    addr->sin_addr.s_addr = inet_addr("127.0.0.1");


    struct sockaddr *addr2 = (struct sockaddr *)addr; // создаем новый поинтер 
                                                      // который указывает на ту же память
                                                      // но якобы там лежит структ sockaddr

    if ( bind(s, addr2, sizeof(struct sockaddr_in)) < 0 ){
          perror ("bind error ");
          return 1;

    }   ;



    addr->sin_port = htons(8080);
    addr->sin_addr.s_addr = inet_addr("127.0.0.1");

    if ( connect(s, addr2, sizeof(struct sockaddr_in)) < 0 ){
           perror ("connect error");
           return 1;
    } ;


    sleep(60);

};




