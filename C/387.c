#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {

    if(argc!=2){
	printf("error: нужен ровно один аргумент\n");
        return 1;
    } 

    int len = atoi(argv[1]);
    if(len <1){
	printf("error: аргумент должен быть  цифра >0\n");
        return 1;
    }


    char source[4] = { '1', '1', 0x00, '1'  };
    printf("source = ");
    for (int i=0; i<4 ;i++){
        printf("0x%hhX ", source[i]);

    }
    printf("\n");


    char *dest = malloc (len);
    memset(dest, 0x32, len);
    printf("dest =   ");
    for (int i=0; i<len ;i++){
        printf("0x%hhX ", dest[i]);

    }
    printf("\n");


    printf("make strncpy\n");
    strncpy(dest, source, len);

    printf("dest =   ");
    for (int i=0; i<len ;i++){
        printf("0x%hhX ", dest[i]);

    }
    printf("\n");




return 0;
}



