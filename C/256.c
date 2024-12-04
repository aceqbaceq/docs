#define _XOPEN_SOURCE 600
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
  md = open("/home/noroot/temp/nc/fifo2", O_RDONLY);

// читаю 
  char buffer[256];
  int len = read(md, buffer, sizeof(buffer) - 1);
     if (len > 0) {
            buffer[len] = '\0';  // Null-terminate the string
            printf("READ DATA FROM md : %s", buffer);
     }



  sleep(120);
  close (md);



exit (0);


}













