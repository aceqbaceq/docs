#include<stdio.h>
#include<time.h>


int main()
{

     const struct timespec kuku = {300, 100};
     struct timespec kuku2 = {3, 100};

     nanosleep(&kuku, &kuku2);


    return 0;
}








