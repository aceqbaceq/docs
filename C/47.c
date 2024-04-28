#include <limits.h>
#include <stdio.h>

// программа посвящена типам даннных


int main(){

// unsigned char вроде как самое малое по размеру тип целого которое можно выделить по переменную
unsigned char a = 1;
unsigned char b = 120;
unsigned char c = a+b;  // проверяем что с типом char можно делать классическую арифметику
printf ( "c=%c\n", c ); // печать как char
printf ( "c=%d\n", c ); // пробуем печататаь как целое надеяст что printf сконвертррует налету и проверяем что арифметика сработала

// проверяем размер под ячейку сколко выделено в байтах
char s_c = sizeof ( c );
printf( "size of var c = %d bytes\n", (int)s_c );    // для печати конвертируем char в int через (int)s_c

unsigned int d = (int) c;
printf ( "d=%d\n", d );


printf( "%p, %p, %p, %p, %p\n" , &a, &b, &c, &s_c, &d );	// смотрим всем ли перееменным был назначен четный адерс в памяти

void *d_Ptr = &b;


return (0);
};