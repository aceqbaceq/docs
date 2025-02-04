#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if_tun.h>
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define TAP_DEVICE "/dev/net/tun"  // Путь к TAP-устройствам
#define TAP_NAME "tap0"            // Имя интерфейса

// Функция для расчёта контрольной суммы ICMP
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    for (; len > 1; len -= 2) sum += *buf++;
    if (len == 1) sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

// Функция для открытия TAP-интерфейса
int open_tap(const char *dev) {
    int fd = open(TAP_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Ошибка открытия TAP-устройства");
        exit(1);
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) {
        perror("Ошибка настройки TAP-интерфейса");
        close(fd);
        exit(1);
    }

    return fd;
}

int main() {
    int tap_fd = open_tap(TAP_NAME);

    unsigned char buffer[1500];  // Буфер для пакета
    memset(buffer, 0, sizeof(buffer));

    // Указатели на структуры заголовков
    struct ethhdr *eth = (struct ethhdr *)buffer;
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    struct icmphdr *icmp = (struct icmphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));

    // Заполняем Ethernet-заголовок
    eth->h_dest[0] = 0x08; eth->h_dest[1] = 0x00; eth->h_dest[2] = 0x27;  // MAC назначения
    eth->h_dest[3] = 0xaa; eth->h_dest[4] = 0xbb; eth->h_dest[5] = 0xcc;

    eth->h_source[0] = 0x08; eth->h_source[1] = 0x00; eth->h_source[2] = 0x27;  // MAC источника
    eth->h_source[3] = 0xdd; eth->h_source[4] = 0xee; eth->h_source[5] = 0xff;

    eth->h_proto = htons(ETH_P_IP);  // Тип пакета: IPv4

    // Заполняем IP-заголовок
    ip->ihl = 5;
    ip->version = 4;
    ip->tos = 0;
    ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct icmphdr));
    ip->id = htons(54321);
    ip->frag_off = 0;
    ip->ttl = 64;
    ip->protocol = IPPROTO_ICMP;
    ip->saddr = inet_addr("172.16.10.12");  // IP источника
    ip->daddr = inet_addr("172.16.10.1");   // IP назначения

    ip->check = checksum(ip, sizeof(struct iphdr));

    // Заполняем ICMP-заголовок (Echo Request)
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = htons(1);
    icmp->un.echo.sequence = htons(1);
    icmp->checksum = 0;
    icmp->checksum = checksum(icmp, sizeof(struct icmphdr));

    // Отправляем пакет в TAP-интерфейс
    int packet_size = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct icmphdr);
    if (write(tap_fd, buffer, packet_size) < 0) {
        perror("Ошибка отправки пакета");
        close(tap_fd);
        exit(1);
    }

    printf("ICMP Ping отправлен через %s -> 172.17.9.2\n", TAP_NAME);

    close(tap_fd);
    return 0;
}


