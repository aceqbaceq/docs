#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

enum {SECS_TO_SLEEP = 3, NSEC_TO_SLEEP = 125};

int main() {
    struct timespec remaining, request = {SECS_TO_SLEEP, NSEC_TO_SLEEP};
    nanosleep(&request, &remaining);

    return(0);
}



