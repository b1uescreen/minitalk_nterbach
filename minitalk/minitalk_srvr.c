/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_srvr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:00:56 by nterbach          #+#    #+#             */
/*   Updated: 2023/05/31 18:21:28 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>

static void	decode(int sgn);

/*
	Starts a server that prints its own PID on startup. The server expects
	to receive the signals SIGUSR1 and/or SIGUSR2 and interpretes them as
	0 and 1 respectively. More details are in the "decode" funtion.
	The server waits for signals until a "kill" command is received.
*/
int	main(void)
{
	int					pid_int;
	pid_t				pid;
	struct sigaction	s_sig_act;

		pid = getpid();
		pid_int = (int) pid;
	ft_printf("%d\n", pid_int);
	s_sig_act.sa_handler = decode;
	sigemptyset(&s_sig_act.sa_mask);
	s_sig_act.sa_flags = 0;
	sigaction(SIGUSR1, &s_sig_act, NULL);
	sigaction(SIGUSR2, &s_sig_act, NULL);
	while (1)
	{
		sleep(4);
	}
	return (0);
}

/*
	Decodes binary signals SIGUSR1 and SIGUSR2 into ASCII characters with
	7 bits. The first signal received will be interpreted as the least
	significant bit of the binary representation. Every consecutive signal
	will be treated as the next lowest significance until it resets after 7
	signals. A fully decoded character is written to the console immediately.
*/
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
