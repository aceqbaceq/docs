#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    struct sockaddr_storage ss; // Структура для хранения адреса
    struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&ss; // Указатель для IPv6

    // Очистим структуру
    memset(&ss, 0, sizeof(ss));

    // Настроим адрес для IPv6
    addr6->sin6_family = AF_INET6;  // Установим семейство адресов для IPv6
    addr6->sin6_port = htons(80);   // Порт 80
    inet_pton(AF_INET6, "fe80::42:3cff:fefa:b542", &(addr6->sin6_addr));  // IP-адрес fe80::42:3cff:fefa:b542

    // Выводим информацию об IPv6
    printf("IPv6 Family: %d\n", addr6->sin6_family);
    printf("IPv6 Address: ");
    for (int i = 0; i < sizeof(addr6->sin6_addr.s6_addr); i++) {
        printf("%02x ", (unsigned char)addr6->sin6_addr.s6_addr[i]);
    }
    printf("\n");

    // Выводим содержимое __ss_padding
    printf("__ss_padding content (in hex):\n");
    for (int i = 0; i < sizeof(ss.__ss_padding); i++) {
        printf("%02x ", (unsigned char)ss.__ss_padding[i]);
    }
    printf("\n");

    return 0;
}

