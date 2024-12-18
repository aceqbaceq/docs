#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    /// мы сейчас будем совать 127.0.0.1 и 8080 в sockaddr используя его формат 

    struct sockaddr addr;

    // 1. Установим семейство адресов в AF_INET (IPv4)
    addr.sa_family = AF_INET;

    // 2. Преобразуем IP в бинарный формат
    const char *ip = "127.0.0.1"; 
    unsigned short port = 8080;

    // 3. Записываем порт в первые 2 байта sa_data (формат big-endian)
    addr.sa_data[0] = (port >> 8) & 0xFF;  // Старший байт порта
    addr.sa_data[1] = port & 0xFF;         // Младший байт порта

    // 4. Записываем IP в следующие 4 байта sa_data
    struct in_addr in_addr;
    inet_pton(AF_INET, ip, &in_addr);  // Преобразуем строку IP в бинарный формат
    memcpy(&addr.sa_data[2], &in_addr.s_addr, 4);  // Копируем 4 байта IP

    // Печать результатов для проверки
    printf("sa_family: %d\n", addr.sa_family);
    printf("sa_data (port): %02x %02x\n", addr.sa_data[0], addr.sa_data[1]);
    printf("sa_data (IP): %02x %02x %02x %02x\n",
           (unsigned char)addr.sa_data[2], (unsigned char)addr.sa_data[3],
           (unsigned char)addr.sa_data[4], (unsigned char)addr.sa_data[5]);



    /// а теперь мы возьмем поинтер  который указвает на sockaddr и убедимся что полученные байты
    /// полностью соотсветуют формату sockaddr_in  на бинарном уровне и мы считаем из памяти данные
    /// как бутто это не sockaddr а sockadrr_in и убедимся что получим обратно 127.0.0.1 и 8080
    struct sockaddr_in *sa1 = (struct sockaddr_in *)&addr;
    printf ("\n"
            "Socket Protocol familty = %hi, "
            "port = %hi, "
            "IPv4 = %s "
            "\n\n", 
            (unsigned short int)sa1->sin_family, ntohs(sa1->sin_port), inet_ntoa(sa1->sin_addr)    );




    


    return 0;
}


