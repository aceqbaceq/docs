// my first program on C
#include <stdio.h>
#include <unistd.h>

int main ()
{

int vasya = 15;
int *pvasya = &vasya;

printf ( "$vasya = %d\n", vasya  );
printf ( "$vasya = %d\n", *pvasya );
printf ( "*pvasya = %p\n", (void *) pvasya );


vasya = 16;
printf ( "new $vasya = %d\n", vasya );

*pvasya = 17;
printf ( "new $vasya = %d\n", *pvasya );


return 0;
}



