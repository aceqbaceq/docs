#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/if_tun.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>


#define TUN_DEVICE "/dev/net/tun"
#define BUFSIZE 2048

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    for (; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    return ~sum;
}

int open_tun(const char *dev) {
    struct ifreq ifr;
    int fd = open(TUN_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open_tun: open");
        exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;  // Создаём TUN без 4-байтового заголовка
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) {
        perror("open_tun: ioctl");
        close(fd);
        exit(1);
    }

    return fd;
}

int main() {
    int tun_fd = open_tun("tun0");
    char buffer[BUFSIZE];

    printf("Listening on tun0 for ICMP packets...\n");

    while (1) {
        int nread = read(tun_fd, buffer, sizeof(buffer));
        if (nread < 0) {
            perror("Read error");
            break;
        }

        printf("получен ping \n");

        struct iphdr *ip = (struct iphdr *)buffer;
        if (ip->protocol == IPPROTO_ICMP) {
            struct icmphdr *icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));

            if (icmp->type == ICMP_ECHO) {  // Ping request
                printf("Received ICMP Echo Request from %s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));

                // Swap source and destination IPs
                uint32_t temp_ip = ip->saddr;
                ip->saddr = ip->daddr;
                ip->daddr = temp_ip;

                // Modify ICMP header for Echo Reply
                icmp->type = ICMP_ECHOREPLY;
                icmp->checksum = 0;
                icmp->checksum = checksum(icmp, nread - (ip->ihl * 4));

                // Send back the modified packet
                write(tun_fd, buffer, nread);
                printf("Sent ICMP Echo Reply to %s\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
            }
        }
    }

    close(tun_fd);
    return 0;
}


