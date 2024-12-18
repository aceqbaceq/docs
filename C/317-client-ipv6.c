#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


void ping(int s, char *message)
{
    char buf[8192];

    strncpy(buf, message, sizeof(buf));
    send(s, buf, strlen(buf), 0);
    recv(s, buf, 8192, 0);
    strtok(buf, "\n");
    puts(buf);
}

int  main(int argc, char *argv[]) {



    // проверяю что программы была запущена с 2 аргументом
        if(argc != 3)
    {
    printf("\n Usage: %s <IPv6> <port> \n",argv[0]);
    return (1);
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
    }




    int s;
    struct sockaddr_in6 addr6;

    s = socket(AF_INET6, SOCK_STREAM, 0);
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(atoi(argv[2]));
    inet_pton(AF_INET6, argv[1], &addr6.sin6_addr);
    
    
    //печатаю ipv6 и порт
    printf("\nIPv6 адрес = %s\n"
           "port = %s\n", argv[1], argv[2]);
    
    // SOCKADDR_IN6 печатаю структуру  структа
        printf("\n\n\n");
        printf("sockaddr_in6              SIZE = %i\n"
               "sockaddr_in.sin6_family   SIZE = %i\n"
               "sockaddr_in.sin6_port     SIZE = %i\n"
               "sockaddr_in.sin6_flowinfo SIZE = %i\n"
               "sockaddr_in.sin6_addr     SIZE = %i\n"
               "sockaddr_in.sin6_scope_id SIZE = %i\n\n",
               sizeof(addr6), sizeof(addr6.sin6_family), sizeof(addr6.sin6_port), sizeof(addr6.sin6_flowinfo), 
               sizeof(addr6.sin6_addr), sizeof(addr6.sin6_scope_id));

    // печатаю содержимое структа
    printf("контент sockaddr_in6     : ");
    for (int i = 0; i < sizeof(addr6); i++) {
        printf("%02x ", ((unsigned char*)&addr6)[i]  );
    }
    printf("\n");


    
    connect(s, (struct sockaddr *)&addr6, sizeof(addr6));

    ping(s, "hoge\n");
    ping(s, "fuga\n");
    ping(s, "piyo\n");

    close(s);
    return 0;
}



