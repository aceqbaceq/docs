
#include <signal.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

// Global variable, shared between the main program and
// the SIGINT handler. The handler will set this variable to 1
// when we press ctrl-c.
// Declared volatile to avoid caching due to compiler optimization
volatile int	g_unblock_sigquit = 0;

// Blocks the specified signal
void	block_signal(int signal)
{
//	Set of signals to block
    sigset_t	sigset;

//	Initialize set to 0
    sigemptyset(&sigset);
//	Add the signal to the set
    sigaddset(&sigset, signal);
//	Add the signals in the set to the process' blocked signals
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    if (signal == SIGQUIT)
	printf("\e[36mSIGQUIT (ctrl-\\) blocked.\e[0m\n");
}

// Unblocks the given signal
void	unblock_signal(int signal)
{
//	Set of signals to unblock
    sigset_t	sigset;

//	Initialize the set to 0
    sigemptyset(&sigset);
//	Add the signal to the set
    sigaddset(&sigset, signal);
//	Remove set signals from the process' blocked signals
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    if (signal == SIGQUIT)
	printf("\e[36mSIGQUIT (ctrl-\\) unblocked.\e[0m\n");
}

// SIGINT signal handler
void	sigint_handler(int signal)
{
    if (signal != SIGINT)
	return ;
//	Blocks other SIGINT signals to protect the global
//	variable during access
    block_signal(SIGINT);
    g_unblock_sigquit = 1;
    unblock_signal(SIGINT);
}

void set_signal_action(void)
{
//	Declare sigaction structure
    struct sigaction	act;

//	Initialize structure to 0.
    bzero(&act, sizeof(act));
//	Add new signal handler
    act.sa_handler = &sigint_handler;
//	Apply new signal handler to SIGINT (ctrl-c)
    sigaction(SIGINT, &act, NULL);
}

int	main(void)
{
//	Change the default action for SIGINT (ctrl-c)
    set_signal_action();
//	Block the SIGQUIT signal (ctrl-\)
    block_signal(SIGQUIT);
//	Infinite loop to give us time to do ctrl-\ and ctrl-c
//	as many times as we wish
    while(1)
    {
//		Block the SIGINT signal while global variable is read
	block_signal(SIGINT);
//		If SIGINT signal handler set the global variable
	if (g_unblock_sigquit == 1)
	{
//			SIGINT (ctrl-c) was received.
	    printf("\n\e[36mSIGINT detected. Unblocking SIGQUIT\e[0m\n");
//			Unblock SIGINT and SIGQUIT
	    unblock_signal(SIGINT);
	    unblock_signal(SIGQUIT);
	}
//		Otherwise, unblock SIGINT and keep looping
	else
	    unblock_signal(SIGINT);
	sleep(1);
    }
    return (0);
}











