#define _XOPEN_SOURCE 600
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>






int main()
{

  pid_t pid_p = getpid();
  printf("parent PID = %d\n", pid_p);


  int md = -1;
  md = open("/home/noroot/temp/nc/fifo2", O_WRONLY);

  dprintf (md, "hello vasya\n");
  sleep(120);
  close (md);



exit (0);


}













