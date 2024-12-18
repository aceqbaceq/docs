#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    struct sockaddr_in addr4;   // Для IPv4
    struct sockaddr sa;
    struct sockaddr_in6 addr6;  // Для Ipv6

    printf ("сравниваю sockaddr_in и sockaddr: \n");

    printf("sockaddr_in              SIZE = %i\n"
           "sockaddr_in.sin_family   SIZE = %i\n"
           "sockaddr_in.sin_port     SIZE = %i\n"
           "sockaddr_in.sin_addr     SIZE = %i\n"
           "sockaddr_in.sin_zero     SIZE = %i\n\n",
           sizeof(addr4), sizeof(addr4.sin_family), sizeof(addr4.sin_port), sizeof(addr4.sin_addr), sizeof(addr4.sin_zero));

    printf("sockaddr              SIZE = %i\n"
           "sockaddr.sa_family    SIZE = %i\n"
           "sockaddr.sa_data      SIZE = %i\n\n",
           sizeof(sa), sizeof(sa.sa_family), sizeof(sa.sa_data));




    // SOCKADDR_IN
    // Настроим адрес для IPv4
    memset(&addr4, 0, sizeof(addr4));
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(80);  // Порт 80 он же 0x50
    inet_pton(AF_INET, "1.2.3.4", &(addr4.sin_addr));  // IP-адрес 1.2.3.4

     // это чисто отклненеие в сторону. захотел скопиротть поле из структа в ообычный тип переменной
    // sa_family_t  b = addr4.sin_family;
    // printf ("размер sa_family_t = %i, b= %i \n", sizeof(b), b);

    // Копируем данные в структуру sockaddr
    memset(&sa, 0, sizeof(sa));
    memcpy(&sa, &addr4, sizeof(struct sockaddr_in));


    // печатаю содержимое каждого поля  addr4
    printf("контент sockaddr_in  : ");
    for (int i = 0; i < sizeof(addr4); i++) {
        printf("%02x ", ((unsigned char*)&addr4)[i]  );
    }
    printf("\n");


    // SOCKADDR
    // печатаю содержимое каждого поля  sa
    printf("контент sockaddr     : ");
    for (int i = 0; i < sizeof(sa); i++) {
        printf("%02x ", ((unsigned char*)&sa)[i]  );
    }
    printf("\n");


    //SOCKADR_IN6
        printf("\n\n\n");
        printf ("теперь проcто  расматриваю  что там внутри sockaddr_in6: \n");
        printf("sockaddr_in6              SIZE = %i\n"
               "sockaddr_in.sin6_family   SIZE = %i\n"
               "sockaddr_in.sin6_port     SIZE = %i\n"
               "sockaddr_in.sin6_flowinfo SIZE = %i\n"
               "sockaddr_in.sin6_addr     SIZE = %i\n"
               "sockaddr_in.sin6_scope_id SIZE = %i\n\n",
               sizeof(addr6), sizeof(addr6.sin6_family), sizeof(addr6.sin6_port), sizeof(addr6.sin6_flowinfo), 
               sizeof(addr6.sin6_addr), sizeof(addr6.sin6_scope_id));






    return 0;
}


