#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

void main();




void main() {


// уточняю чему равен INET_ADDRSRLEN
printf ("INET_ADDRSTRLEN = %i \n", INET_ADDRSTRLEN );
printf ("============\n");


// задаю ipv4 адрес в hex виде, меняю в нем порядок битов на обратный тоесть NeworkOrder делаю
// и всовываю его в структуру in_addr в поле s_addr 
struct in_addr ia;
ia.s_addr = htonl(0x12131415);

// задаю пустую болванку char длинной как ipv4
char ch1[INET_ADDRSTRLEN];

// подтставляю эти пременные сюда. чтобы inet_ntop мне преобразовала ipv4 адрес из бинарного вида 
// в текстовый вид 
// чтение идет из sa а запись идет в ch1
inet_ntop(AF_INET, &ia, ch1, INET_ADDRSTRLEN);


// печатаю результат мой ipv4=12.13.14.15 в hex представлении
// будет в обычном представлении как 18.19.20.21 что верно 
printf("ipv4 = %s\n", ch1);  
printf ("============\n");


// 
inet_pton(AF_INET, "20.21.22.23", &ia);
inet_ntop(AF_INET, &ia, ch1, INET_ADDRSTRLEN);
printf("ipv4 = %s\n", ch1);  
printf ("============\n");



// 
printf ("new section \n");
char ip2 [INET_ADDRSTRLEN] = "23.24.25.26";

struct in_addr ia2;
    if ( inet_pton(AF_INET, ip2, &ia2) ==0){
           printf ("Conversion error\n");
        };


char ch2[INET_ADDRSTRLEN];
inet_ntop(AF_INET, &ia2, ch2, INET_ADDRSTRLEN);

printf("ipv4 = %s\n", ch2);  
printf ("============\n");




// 
printf ("new section \n");
char ip3 [INET_ADDRSTRLEN] = "26.27.28.29";

struct sockaddr_in sa3;

    if ( inet_pton(AF_INET, ip3, &(sa3.sin_addr)) ==0){
           printf ("Conversion error\n");
        };


char ch3[INET_ADDRSTRLEN];
inet_ntop(AF_INET, &(sa3.sin_addr), ch3, INET_ADDRSTRLEN);

printf("ipv4 = %s\n", ch3);  
printf ("============\n");





}