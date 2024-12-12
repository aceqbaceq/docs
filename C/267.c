/* --- server.c --- */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#define SIZE 4096

int main(int argc, char *argv[])
{



    // проверяю что программы была запущена с двумя аргументами
    if(argc != 3)
    {
    printf("\n Usage: %s <ip of server>  <port> \n",argv[0]);
    return 1;
    }

    // печатаю считанные аргументы
    for (int i=0; i<argc; i++)
    {
    printf("argv[%d] = %s\n", i, argv[i]);
    }





    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    
    time_t ticks;


    char sendBuff[SIZE];
    
    // Инициализация генератора случайных чисел
    srand((unsigned int)time(NULL));
    
    // Заполнение массива случайными символами
    for (int i = 0; i < SIZE; i++) {
        // Генерация случайного символа (например, печатные ASCII символы от ' ' до '~')
        sendBuff[i] = (rand() % 95) + 32;  // Генерация символов от ' ' (32) до '~' (126)
    }
    



    /* creates an UN-named socket inside the kernel and returns
     * an integer known as socket descriptor
     * This function takes domain/family as its first argument.
     * For Internet family of IPv4 addresses we use AF_INET
     */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( atoi(argv[2]) );  // сую порт в структ

    // преобразую ip адрес сервера из TXT в NET и сую его в структ
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
    printf("\n inet_pton error occured\n");
    return 1;
    }






    /* The call to the function "bind()" assigns the details specified
     * in the structure 『serv_addr' to the socket created in the step above
     */
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /* The call to the function "listen()" with second argument as 10 specifies
     * maximum number of client connections that server will queue for this listening
     * socket.
     */
    listen(listenfd, 10);

    while(1)
    {
	/* In the call to accept(), the server is put to sleep and when for an incoming
	 * client request, the three way TCP handshake* is complete, the function accept()
	 * wakes up and returns the socket descriptor representing the client socket.
	 */
	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

	/* As soon as server gets a request from client, it prepares the date and time and
	 * writes on the client socket through the descriptor returned by accept()
	 */
	ticks = time(NULL);
	//snprintf(sendBuff, sizeof(sendBuff), "123\n");
        for (int i = 0; i < 100; i++) {
		write(connfd, sendBuff, strlen(sendBuff));
        sleep(2);
        }

        sleep (60);
	close(connfd);
	sleep(1);
    }
}

