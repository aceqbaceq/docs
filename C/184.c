/*

the program tests how a semaphore works

*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SEM_KEY 0x1234
#define num_proc 6



char const f_path[] = "/tmp/5.txt";



int consume(int semid)
{


    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);


    int fd = open(f_path, O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    char prev[10]="000000000";
    int ret = read(fd, prev, sizeof(prev));
    off_t ret2 = lseek(fd, 0, SEEK_SET);
    char cur[10]="000000000";
    int pid = getpid();
    sprintf(cur,"%d", pid);
    ret = write(fd, cur, sizeof(cur));
    ret = read(fd, cur, sizeof(cur));
    close(fd);

    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    semop(semid, &sem_op, 1);

    printf("pid = %i, prev  =  %s, cur  %s \n", pid, prev, cur);
}

int main()
{

    int fd = open(f_path, O_RDWR|O_CREAT|O_TRUNC, 0666);
    char const ini[]="000000000";
    int ret = write(fd, ini,sizeof(ini));
    close(fd);


    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid < 0)
    {
        perror("semget");
        return 1;
    }

    if (semctl(semid, 0, SETVAL, 1) < 0)
    {
        perror("semctl");
        return 1;
    }

    for (int j = 1; j<num_proc; j++){
        ret = fork();
        if (ret == -1)
        {
           perror("fork");
           return 1;
        }
        else if (ret == 0)
             break;
        }

    //srand(getpid());
    //int rnd_n = ( rand() % 3 ) + 1;
    //printf ("pid = %i, sleep interval = %i \n", getpid(), rnd_n);
    for (int i = 0; i < 3; i++)
    {
        consume(semid);
        //sleep(rnd_n);
    }



    if (ret !=0)
    {
        printf ("pid = %i. Main process has finished the work. Waiting for children to finish the work \n", getpid());
        while (errno != ECHILD)
        {
            wait(NULL);
        }
        printf ("pid = %i. All children has finished the work. Main process is exiting. \n", getpid());


    }

    return 0;
}


