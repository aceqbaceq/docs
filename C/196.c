#include <sys/socket.h>
#include <netinet/in.h>

void main() {

// int vasya = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
  int petya = socket(AF_INET, SOCK_RAW, IPPROTO_IPIP);


}





