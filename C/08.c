// my first program on C
#include <stdio.h>
#include <unistd.h>

int main ()
{


int vasya = 1;
int *pvasya = &vasya;

// printf ( "address = %x\n", &vasya );
printf ( "hex=%x\n", vasya );
printf("symbolic=%s int=%d float=%f single char=%c\n", "Sam", 14, -8.76, 'X');
printf ( "decimal number = %d\n", 1);
printf ( "unsigned long hex number = %lx\n", 0x7ffc227903cc );
printf ( "address = %p\n", (void *) &vasya );

return 0;
}



