#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void sigdown(int signo) {
  psignal(signo, "Shutting down, got signal");
  exit(0);
}


static void sigterm(int signo) {
  printf("SIGTERM is caught....shutting down\n");
  exit(0);
}

static void sighup(int signo) {
  printf("SIGHUP is caught....shutting down\n");
  exit(0);
}




static void sigreap(int signo) {
  while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {

  if (sigaction(SIGINT, &(struct sigaction){.sa_handler = sigdown}, NULL) < 0)
    return 1;
  if (sigaction(SIGTERM, &(struct sigaction){.sa_handler = sigterm}, NULL) < 0)
    return 2;

  if (sigaction(SIGHUP, &(struct sigaction){.sa_handler = sighup}, NULL) < 0)
    return 3;


  if (sigaction(SIGCHLD, &(struct sigaction){.sa_handler = sigreap,
                                             .sa_flags = SA_NOCLDSTOP},
                NULL) < 0)
    return 4;

  for (;;)
    pause();
  fprintf(stderr, "Error: infinite loop terminated\n");
  return 42;
}

