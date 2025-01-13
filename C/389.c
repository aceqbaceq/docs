#include <stdio.h>



int main() {
   
    char a = 0x10;
    char *p[2] = { &a, NULL };

    int i = 0;
    while (p[i] != NULL) {
	printf ("i = %i, p[%i] != NULL \n",    i, i);
	i++;
    } 


return 0;
}


