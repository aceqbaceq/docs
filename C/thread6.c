#include <sys/syscall.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])   {

    pid_t pid = atoi(argv[1]);  // Идентификатор процесса
    pid_t tid = atoi(argv[2]);     // Идентификатор потока
    
    // Вызов tgkill через syscall
    syscall(SYS_tgkill, pid, tid, SIGINT);

    return 0;
}



