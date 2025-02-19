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
#include <netinet/ether.h>

#define TAP_DEVICE "/dev/net/tun"
#define BUFSIZE 2048
#define TAP_NAME "tap5"

// Функция для открытия TAP-интерфейса
int tap_alloc(const char *dev) {
    struct ifreq ifr;
    int fd = open(TAP_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open /dev/net/tun");
        exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;  // TAP-интерфейс, без прото-заголовков
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) {
        perror("ioctl TUNSETIFF");
        close(fd);
        exit(1);
    }

    return fd;
}

// Функция вычисления контрольной суммы
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
    int tap_fd = tap_alloc("TAP_NAME");
    unsigned char buffer[BUFSIZE];

    printf("TAP listener started on %s...\n", TAP_NAME);

    while (1) {
        int len = read(tap_fd, buffer, sizeof(buffer));
        if (len < 0) {
            perror("read");
            break;
        }

        struct ethhdr *eth = (struct ethhdr *)buffer;
        if (ntohs(eth->h_proto) != ETH_P_IP) continue; // Фильтруем только IPv4

        struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
        struct icmphdr *icmp = (struct icmphdr *)(buffer + sizeof(struct ethhdr) + (ip->ihl * 4));

        // Если это ICMP Echo Request (ping)
        if (ip->protocol == IPPROTO_ICMP && icmp->type == ICMP_ECHO) {
            printf("Received ICMP Echo Request from %s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));

            // Меняем MAC-адреса
            unsigned char tmp_mac[ETH_ALEN];
            memcpy(tmp_mac, eth->h_source, ETH_ALEN);
            memcpy(eth->h_source, eth->h_dest, ETH_ALEN);
            memcpy(eth->h_dest, tmp_mac, ETH_ALEN);

            // Меняем src и dst IP
            uint32_t src_ip = ip->saddr;
            ip->saddr = ip->daddr;
            ip->daddr = src_ip;

            // Меняем ICMP-заголовок (Echo Request -> Echo Reply)
            icmp->type = ICMP_ECHOREPLY;
            icmp->checksum = 0;
            icmp->checksum = checksum(icmp, len - sizeof(struct ethhdr) - (ip->ihl * 4));

            // Отправляем обратно через TAP
            write(tap_fd, buffer, len);
            printf("Sent ICMP Echo Reply to %s\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
        }
    }

    close(tap_fd);
    return 0;
}
