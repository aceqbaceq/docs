#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void sigdown(int signo) {
  pid_t pid_p = getpid();
  printf("parent: WARNING parent PID=%d...\n", pid_p);
  psignal(signo, "parent: Shutting down, got signal");
  exit(0);
}






int main() {
   pid_t pid_p = getpid();
   printf("parent: parent PID=%d...\n", pid_p);




  if (sigaction(SIGINT, &(struct sigaction){.sa_handler = sigdown}, NULL) < 0)
    return 1;
  if (sigaction(SIGTERM, &(struct sigaction){.sa_handler = sigdown}, NULL) < 0)
    return 2;

  for (;;)
    pause();
  fprintf(stderr, "Error: infinite loop terminated\n");
  return 42;
}

