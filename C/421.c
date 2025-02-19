#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>


#define TUN_DEVICE "/dev/net/tun"
#define BUFSIZE 2048

// Функция для открытия TUN-интерфейса
int tun_alloc(const char *dev) {
    struct ifreq ifr;
    int fd = open(TUN_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open /dev/net/tun");
        exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;  // TUN-интерфейс, без прото-заголовков
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) {
        perror("ioctl TUNSETIFF");
        close(fd);
        exit(1);
    }

    return fd;
}

// Функция для вычисления контрольной суммы IP/ICMP
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    for (sum = 0; len > 1; len -= 2) sum += *buf++;
    if (len == 1) sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return ~sum;
}

int main() {
    int tun_fd = tun_alloc("tun0");
    unsigned char buffer[BUFSIZE];

    printf("TUN listener started on tun0...\n");

    while (1) {
        int len = read(tun_fd, buffer, sizeof(buffer));
        if (len < 0) {
            perror("read");
            break;
        }

        struct iphdr *ip = (struct iphdr *)buffer;
        struct icmphdr *icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));

        // Если это ICMP Echo Request (ping)
        if (ip->protocol == IPPROTO_ICMP && icmp->type == 8) {
            printf("Received ICMP Echo Request from %s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));

            // Меняем src и dst IP местами
            uint32_t src_ip = ip->saddr;
            ip->saddr = ip->daddr;
            ip->daddr = src_ip;

            // Меняем ICMP-заголовок (Echo Request -> Echo Reply)
            icmp->type = 0;
            icmp->checksum = 0;
            icmp->checksum = checksum(icmp, len - (ip->ihl * 4));

            // Отправляем обратно через TUN
            write(tun_fd, buffer, len);
            printf("Sent ICMP Echo Reply to %s\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
        }
    }

    close(tun_fd);
    return 0;
}

