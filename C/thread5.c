#define _GNU_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <stdlib.h>

#define TGKILL 270


int main(int argc, char *argv[])
{
    long ret;
    int tgid, tid;

    tgid = atoi(argv[1]);
    tid = atoi(argv[2]);

    ret = syscall(TGKILL, tgid, tid, SIGTERM);

    if (ret != 0)
        perror("tgkill");

    return 0;
}

