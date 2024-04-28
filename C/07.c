// my first program on C
#include <stdio.h>
#include <unistd.h>

int main ()
{

int fd;
fd = 0;

void *pbuf;
char bufer[10];
pbuf = &bufer;

size_t a;
a = 10;

read ( fd, pbuf, a );
write ( fd, pbuf, a);
printf ( "\n" );


return 0;
}



