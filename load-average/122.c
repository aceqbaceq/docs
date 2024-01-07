#include <stdio.h>
#include <time.h>
#include<unistd.h>

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(void) {
    clock_t t1, t2;
    int i;
    long elapsed;


while(1) {
    long settime = 50;   
    t1 = clock();
    for (i=0; i < 10000000000; i++) {
	t2 = clock();
	elapsed = timediff(t1, t2);
	if (elapsed>=settime)
	     {
		//printf("set time reached\n"); 
        	break;}

    }

    sleep(5);


     // printf("elapsed: %ld ms\n", elapsed); 

}

    return 0;
}
