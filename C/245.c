#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

                // Note: STDIN_FILENO, or fileno(stdin)
#define STDIN 0  // file descriptor for standard input

int main(void)
{
   fd_set readfds, temp;
   struct timeval tv;
   int ret,ch;

   FD_ZERO(&readfds);
   FD_ZERO(&temp);
   FD_SET(STDIN, &readfds);

   while(1){

        temp = readfds;
        tv.tv_sec = 2;
        tv.tv_usec = 500000;
        // don't care about writefds and exceptfds:
        ret = select(STDIN+1, &temp, NULL, NULL, NULL) ;
        if (ret == -1) {
                if (errno == EAGAIN) continue; // These are NOT Errors, but natural occuring events
                if (errno == EINTR) continue; // The are reported to avoid your select() to block for too long
                        perror("erreur");
                break;
                }
        else if (ret ==0) {
           printf("Timed out.\n");
                continue;
                }
                // Ok: select has returned > 0; there must be something to read
        if (FD_ISSET(STDIN, &temp)) {
                ch = getc(stdin); // Lookout: stdin is line-buffered
                printf("A key was pressed: %d!\n", ch);
                }
        }
   return 0;
}


