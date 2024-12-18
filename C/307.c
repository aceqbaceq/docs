#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>

#define PING_PKT_S 64  // Размер пинга в байтах (ICMP Echo Request)
#define PING_SLEEP_RATE 1 // Частота отправки пингов (секунды)


// Структура для вычисления времени отклика
struct ping_pkt {
    struct icmphdr hdr;
    char msg[PING_PKT_S - sizeof(struct icmphdr)];
};


// Функция для расчета контрольной суммы
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
    struct ping_pkt pkt;
    struct timeval tv;
    int ttl_val = 64;  // Время жизни пакета (TTL)

    memset(&pkt, 0, sizeof(pkt));

    // Заполняем ICMP заголовок
    pkt.hdr.type = ICMP_ECHO;  // Тип пакета - запрос
    pkt.hdr.un.echo.id = 123;  // Используем идентификатор процесса

    // Заполняем сообщение
    snprintf(pkt.msg, sizeof(pkt.msg), "Ping message from %s", ip_addr);
    pkt.hdr.un.echo.sequence = 1;



    pkt.hdr.checksum = checksum(&pkt, sizeof(pkt));  // Вычисляем контрольную сумму

    // Устанавливаем TTL (Time to Live)
    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0) {
        perror("setsockopt failed");
        exit(1);
    }

    // Отправляем пакет
    if (sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr*) addr, sizeof(*addr)) <= 0) {
        perror("Send failed");
        exit(1);
    }

    // Получаем время отправки
    printf("Ping Sent \n");
}

// Функция для получения ICMP ответа
void receive_ping(int sockfd) {
    char buffer[1024];
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    struct timeval tv;

    // Получаем данные из сокета
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);
    if (n <= 0) {
        perror("Receive failed");
        exit(1);
    }


    // Получаем время ответа
    printf("Received ICMP reply: %s \n", inet_ntoa(addr.sin_addr));
}

// Основная функция
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IP Address>\n", argv[0]);
        exit(1);
    }

    printf("process PID = %i\n", getpid());

    const char *ip_addr = argv[1];
    struct sockaddr_in addr;
    int sockfd;

    // Создаем сокет
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    addr.sin_addr.s_addr = inet_addr(ip_addr);

    while (1) {
        send_ping(sockfd, &addr, ip_addr);  // Отправляем пинг
        receive_ping(sockfd);  // Получаем ответ
        sleep(PING_SLEEP_RATE);  // Задержка между пингами
    }

    close(sockfd);
    return 0;
}


