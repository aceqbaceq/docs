#define _GNU_SOURCE
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include <assert.h>


// ----------------------------------------------------------------------------
// Name   : sig_handler
// Usage  : Signal handler for SIGWINCH
// Return : None
// ----------------------------------------------------------------------------
static void sig_handler(int sig)
{
  if (SIGWINCH == sig) {
    struct winsize winsz;

    ioctl(0, TIOCGWINSZ, &winsz);
    printf("SIGWINCH raised, window size: %d rows / %d columns\n",
           winsz.ws_row, winsz.ws_col);
  }

} // sig_handler


// ----------------------------------------------------------------------------
// Name   : main
// Usage  : Program's entry point
// Return : 0, if OK
//          !0, if error
// ----------------------------------------------------------------------------
int main(void)
{
  // Capture SIGWINCH
  signal(SIGWINCH, sig_handler);

  while (1) {
    pause();
  }

  return 0;

} // main
