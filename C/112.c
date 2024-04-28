#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h> // for the definition of errno



int main(void)
{


printf ("номер процесса =%i \n", getpid() );


int flags = O_RDONLY;
char *pathname = "/home/vasya/temp/!28/1.txt";
int fd = open(pathname, flags);


if (fd < 0) {
      perror("Creation error");
      printf("An error occurred. errno set to %d\n", errno);
      exit(1);

}

printf ("номер дескриптора = %i \n", fd);


int num=0;          // переменная цикла
int dlina=1;        // сколько символов за раз считываем
int offset_step=1;  // промежуток между офсетами
char buf[dlina];    // куда записываем символы из файла

while ( num<=5 ) {

    int cur_offset = lseek(fd,0,SEEK_CUR);
    ssize_t rr = read(fd, buf, dlina);
    printf ("читаю из файла: оффсет=%i, символ=%s, число прочитанных байт=%zd\n", cur_offset, buf, rr );
    num ++;
    cur_offset += offset_step;
    lseek(fd,cur_offset,SEEK_SET);
    sleep (10);
}


close(fd);
exit (0);

}





