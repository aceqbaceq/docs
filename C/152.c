#include <stdio.h>
#include<time.h>
#include<unistd.h>
int main() {
    int num;
    for (int count = 0; count <= 10; count++)
    {
    printf("count=%d\n", count);
    sleep(1);
    }
    return 0;
}




