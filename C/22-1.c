#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signum)
{
  printf("got SIGINT\n");
}


int main(void)
{
  signal(SIGINT, sigint_handler);
  printf("pid is %d\n", getpid());
  while (1)
  sleep(1);
}
