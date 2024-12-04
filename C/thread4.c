#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>           /* Definition of SIG* constants */
#include <sys/syscall.h>      /* Definition of SYS_* constants */
#include <unistd.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/syscall.h>



int main() {
    pid_t pid = 2967399;  // PID процесса
    int tid = 2967401;     // TID потока
    tgkill(pid, tid, SIGTERM);  // Отправляем сигнал конкретному потоку
    return 0;
}


