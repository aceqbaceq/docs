#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <locale.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{

char b1 ;
b1=17;
printf ("b1=%hhd\n",b1);

char v1[10]="123456789\0";
char *a1;
a1 = v1;
printf ("a1=%s\n",a1);


char const *c1;
c1 = a1;
printf ("c1=%s\n",c1);



const char  *a19 = "vasya";
printf ("%s \n", a19);


char  *a20 = "vasya";
printf ("%s \n", a20);



int i=0;
while(envp[i]) {
  printf("%s\n", envp[i]);
  //do something
  i++;
};


char j1='e';
printf ("\n\n%c\n", j1);


char *j2;
j2 = &j1;
printf ("%c\n",*j2);

printf ("%zu\n", sizeof(j1) );

exit (0);



}





