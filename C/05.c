#include<stdio.h>
int main()
{
    int a = 10;
    void *ptr = &a;
    printf("Integer variable is = %d", *( (int*) ptr) );
    return 0;
}






