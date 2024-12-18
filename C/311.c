#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    // IPV4
    struct sockaddr_in addr;
    struct sockaddr sa;


    // Настроим адрес для IPv4
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);  // Порт 80
    inet_pton(AF_INET, "18.18.18.18", &(addr.sin_addr));  // IP-адрес 18.18.18.18

    // Копируем данные в структуру sockaddr
    memset(&sa, 0, sizeof(sa));
    memcpy(&sa, &addr, sizeof(struct sockaddr_in));

    // Теперь sa.sa_family будет AF_INET, и sa_data будет содержать данные адреса
    printf("Family: %d\n", sa.sa_family);
    printf("Address in sa_data: ");
    for (int i = 0; i < sizeof(sa.sa_data); i++) {
        printf("%02x ", (unsigned char)sa.sa_data[i]);
    }
    printf("\n");


    //IPV6
    struct sockaddr_in6 addr6;
    struct sockaddr sa2;


    // Настроим адрес для IPv6
    memset(&addr6, 0, sizeof(addr6));
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(80);  // Порт 80
    inet_pton(AF_INET6, "fe80::42:3cff:fefa:b542", &(addr6.sin6_addr));  // IP-адрес fe80::42:3cff:fefa:b542

    // Копируем данные в структуру sockaddr
    memset(&sa2, 0, sizeof(sa2));
    memcpy(&sa2, &addr6, sizeof(struct sockaddr_in6));


    // Теперь sa2.sa_family будет AF_INET6, и sa_data будет содержать данные адреса
    printf("Family: %d\n", sa2.sa_family);
    printf("Address in sa_data: ");
    for (int i = 0; i < sizeof(sa2.sa_data); i++) {
        printf("%02x ", (unsigned char)sa2.sa_data[i]);
    }
    printf("\n");



    return 0;
}


