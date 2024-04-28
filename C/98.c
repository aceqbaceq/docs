#include<stdio.h>
int main()
{
    char string[20];
    printf("Enter the string: ");
    fgets(string,20,stdin);       
    printf("\nThe string is: %s",string);
    return 0;
}
