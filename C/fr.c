#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define NB_SECONDS 20

static char *str_second[NB_SECONDS] =
{
  "zero", "one", "two", "three", "four", "five",
  "six", "seven", "eight", "nine", "ten",
  "eleven", "twelve", "thirteen", "fourteen", "fiveteen",
  "sixteen", "seventeen", "eighteen", "nineteen"
};

char data[100];

static int semid;

struct sembuf sembuf_for_P =  {0, -1, SEM_UNDO};
struct sembuf sembuf_for_V =  {0, +1, SEM_UNDO};

#define P(id)  semop(id, &sembuf_for_P, 1)
#define V(id)  semop(id, &sembuf_for_V, 1)

static void *thd_main(void *p)
{
unsigned int i = 0;

 (void)p;

  while(1) {

    // Update the counter in ASCII
    P(semid);
    strcpy(data, str_second[i]);
    V(semid);

    // Wait one second
    sleep(1);

    // Incrementation of the counter in the range [0, NB_SECONDS[
    i = (i + 1) % NB_SECONDS;
  }

  return NULL;
} // thd_main

int main(void)
{
pthread_t      tid;
unsigned short val = 1;

  // Creation of the semaphore
  semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0777);

  // Initialization of the semaphore with the value 1
  semctl(semid, 0, SETALL, &val);

  // Creation of the thread
  (void)pthread_create(&tid, NULL, thd_main, NULL);

  // Interaction with the operator
  while(fgetc(stdin) != EOF) {

    // Display the ASCII value of the counter
    P(semid);
    printf("Current counter value: %s\n", data);
    V(semid);
  }

  return 0;

} // main
