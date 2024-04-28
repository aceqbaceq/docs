#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(void)
{

pid_t pid = getpid();
printf ("PID = %i \n", pid);
int fd = open ("/proc/self/fd/0", O_RDONLY);


if ( fd < 0 ) {
        printf("Opening file : Failed\n");
        printf ("Error no is : %d\n", errno);
        printf("Error description is : %s\n",strerror(errno));
        exit (1);
} 





pid_t fgrp = tcgetpgrp(fd);
pid_t pgrp = getpgrp();
printf ("foreground код возврата  = %i \n", fgrp);
printf ("pgrp  = %i \n", pgrp);


if ( pgrp  == fgrp ) {
	printf("process foregrounded\n");
} else {
	printf("process backgrounded\n");
}


sleep (600);

exit (0);



}





