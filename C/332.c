#include <stdio.h>
#include <stdlib.h>

struct myStruct {
    int length;
    char data[0]; 
};

int main() {


    int data_size = 10; 
    struct myStruct *s = malloc(sizeof(struct myStruct) + data_size);

    if (s == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }



    s->length = data_size;
    for (int i = 0; i < data_size; ++i) {
        *(s->data+i) = 'A' + i;
    }

    free(s);

    return 0;
}

