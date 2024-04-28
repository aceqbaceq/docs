#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int testInteger;
    for (;;)
    {
    printf("Enter an integer: ");
    scanf("%d", &testInteger);  
    printf("Number = %d\n",testInteger);
    sleep(1);
    }

    return 0;
}



