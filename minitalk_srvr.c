#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>

static void	decode(int sgn);

/*
	Please note that VSCode can't check for errors properly.
	It doesn't recognize that there is a definition for "sigaction"
	in <signal.h> and therefore can't make sense of it.
	Compilation should work just fine.
*/
int	main(void)
{
	int		pid_int;
	pid_t	pid;
	struct	sigaction sig_act;

		pid = getpid();
		pid_int = (int) pid;
	ft_printf("%d\n", pid_int);
	sig_act.sa_handler = decode;
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = 0;
	sigaction(SIGUSR1, &sig_act, NULL);
	sigaction(SIGUSR2, &sig_act, NULL);
	while (1)
	{
		sleep(4);
	}
	return (0);
}

static void	decode(int sgn)
{
	static int	mdfr = 1;
	static int	rslt = 0;
	char		c;

	if (sgn == SIGUSR2)
	{
		rslt += mdfr;
	}
	if (mdfr == 64)
	{
		c = (char) rslt;
		rslt = 0;
		write(1, &c, 1);
		mdfr = 1;
	}
	else
	{
		mdfr *= 2;
	}
}
