#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<signal.h>

// five-children.c
static const size_t kNumChildren = 10;
static size_t NumChildrenExit = 0;


static void reapChild(int sig) {
    while (1) {
       pid_t pid = waitpid(-1, NULL, WNOHANG);
       if (pid < 0) break;
       NumChildrenExit++;
    }
}

int main(int argc, char *argv[]) {
  printf("The program is started.\n");

  printf("install signal handlre for SIGCHLD\n");
  signal(SIGCHLD, reapChild); // install signal handler



  // lets create kNumChildren children via fork()
  for (size_t kid = 1; kid <= kNumChildren; kid++) {
    pid_t pid_c = fork();
    if (pid_c > 0){
       printf("Create #%zu child\n", kid);
    };
    if (pid_c == 0) {
      sleep (1);
      printf("Child #%zu is finished the work... -->exit.\n", kid);
      return 0;
    }
  }



  // main loop in parent process
  while (  1  ) {
    sleep(5); // custom fn to sleep uninterrupted
    if (NumChildrenExit == kNumChildren){
       printf("To exit press Ctrl+C.\n");
    };
  }
  return 0;
}


