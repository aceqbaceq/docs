#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[], char *envp[])
{

char a = 12;
char * p_a = &a;
char * * p_p_a = &p_a;
printf ( " &a = %p\n p_a = %p\n &p_a = %p\n " , &a, p_a,  p_p_a  );
printf ("============================\n");


char  path[] = "./155.exe";
//char * * z  = &path;
//printf ( " path = %p\n &path[0] = %p\n &path = %p\n",  path, &path[0], &path     );



int i[ 3 ] = { 1, 2, 3 };
printf (  "%i  \n", i[0]   );
printf (  "%i  \n", i[20]   );
printf ("============================\n");

unsigned int b = sizeof(i);
printf (  "b = %u  \n", b   );
printf ("============================\n");


int * ptr_a1 = NULL;
printf ( " ptr_a1 = %p\n " ,  ptr_a1     );
printf ("============================\n");
if (ptr_a1 == 0 )
printf ("ptr_a1 = 0\n");
if (ptr_a1 == NULL )
printf ("ptr_a1 = NULL\n");


int * ptr_a2 = 0;
printf ( " ptr_a2 = %p\n " ,  ptr_a2     );
printf ("============================\n");

char * ptr_a3 = "vasya";
if ( ptr_a3 )
printf ("ptr_a3 is NOT  NULL\n");


void * ptr_a4 = "vasya";


char ptr_a5[] = "petya";
char q = *(ptr_a5+0);
printf ("q=%c\n", q);
printf ("============================\n");


char c1[] = { 'v', 'a', 0x00 };
char * ptr_c1 = c1;
printf ("%s\n", ptr_c1);
printf ("============================\n");




char c2[] = { 'v', 'a' };
char * ptr_c2 = c2;
printf ("%s\n", ptr_c2);
printf ("============================\n");





exit(0);

}




