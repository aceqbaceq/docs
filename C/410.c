#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TIME 130
#define SIZE 1024*1024*1024


int main() {

    void *p = malloc (SIZE);
    sleep(10);
    memset(p, 0x10, SIZE);
    sleep(130);

return 0;

}

