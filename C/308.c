#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>
 

// Структура для отправки ICMP Echo Request
struct icmp_pkt {
    struct icmphdr hdr;
    char msg[64];  // Сообщение для пинга (макс 64 байта)
};

// Функция для вычисления контрольной суммы
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

// Функция для отправки пинга
void send_ping(int sockfd, struct sockaddr_in *addr, const char *ip_addr) {
    struct icmp_pkt pkt;
    struct timeval tv;

    memset(&pkt, 0, sizeof(pkt));

    // Заполняем ICMP-заголовок
    pkt.hdr.type = ICMP_ECHO;  // Тип ICMP пакета (Echo Request)
//    pkt.hdr.un.echo.id = 123;  // Идентификатор пакета
    snprintf(pkt.msg, sizeof(pkt.msg), "Ping message from %s", ip_addr);  // Тело пакета
//    pkt.hdr.un.echo.sequence = 1;  // Последовательность запроса

    // Вычисляем контрольную сумму
    pkt.hdr.checksum = checksum(&pkt, sizeof(pkt));

    // Отправляем ICMP Echo Request
    if (sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr*) addr, sizeof(*addr)) <= 0) {
        perror("Send failed");
        exit(1);
    }

    gettimeofday(&tv, NULL);
    printf("Ping Sent at: %ld.%06ld seconds\n", tv.tv_sec, tv.tv_usec);
}

// Функция для получения ICMP-ответа
void receive_ping(int sockfd) {
    char buffer[1024];
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    struct timeval tv;

    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);
    if (n <= 0) {
        perror("Receive failed");
        exit(1);
    }

    gettimeofday(&tv, NULL);
    printf("Received ICMP reply: %s at %ld.%06ld seconds\n", inet_ntoa(addr.sin_addr), tv.tv_sec, tv.tv_usec);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IP Address>\n", argv[0]);
        exit(1);
    }

    const char *ip_addr = argv[1];
    struct sockaddr_in addr;
    int sockfd;

    // Создаем сокет с типом SOCK_DGRAM и протоколом IPPROTO_ICMP
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = 0;  // Порт не используется для ICMP
    addr.sin_addr.s_addr = inet_addr(ip_addr);

    // Отправляем пинг и получаем ответ
    send_ping(sockfd, &addr, ip_addr);
    receive_ping(sockfd);

    close(sockfd);
    return 0;
}


