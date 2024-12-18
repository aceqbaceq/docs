#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    struct sockaddr_storage ss; // Структура для хранения адреса
    struct sockaddr_in *addr4 = (struct sockaddr_in *)&ss;  // Указатель для IPv4
    struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&ss; // Указатель для IPv6

    // Пример для IPv4
    memset(&ss, 0, sizeof(ss));  // Очистим структуру
    addr4->sin_family = AF_INET;  // Установим семейство адресов для IPv4
    addr4->sin_port = htons(80);  // Порт 80
    inet_pton(AF_INET, "192.168.1.1", &(addr4->sin_addr));  // Адрес 192.168.1.1

    printf("IPv4 Family: %d\n", addr4->sin_family);
    printf("IPv4 Address: ");
    for (int i = 0; i < sizeof(addr4->sin_addr.s_addr); i++) {
        printf("%02x ", ((unsigned char *)&addr4->sin_addr)[i]);
    }
    printf("\n");


    // Пример для IPv6
    memset(&ss, 0, sizeof(ss));  // Очистим структуру
    addr6->sin6_family = AF_INET6;  // Установим семейство адресов для IPv6
    addr6->sin6_port = htons(80);   // Порт 80
    inet_pton(AF_INET6, "fe80::42:3cff:fefa:b542", &(addr6->sin6_addr));  // Адрес fe80::42:3cff:fefa:b542

    printf("IPv6 Family: %d\n", addr6->sin6_family);
    printf("IPv6 Address: ");
    for (int i = 0; i < sizeof(addr6->sin6_addr.s6_addr); i++) {
        printf("%02x ", (unsigned char)addr6->sin6_addr.s6_addr[i]);
    }
    printf("\n");

    return 0;
}


