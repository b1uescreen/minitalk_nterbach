/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:00:34 by nterbach          #+#    #+#             */
/*   Updated: 2023/05/31 18:36:50 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static void	snd_msg(char *msg, int pid);
static int	ato_pid(const char *str);

/*
	The "client" program expects...
	arg0 to be the path to the executable
	arg1 to be the server PID
	arg2 to be the string to be sent.
*/
int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc == 3)
	{
		pid = ato_pid(argv[1]);
		if (pid == -42)
			return (1);
		else
		{
			snd_msg(argv[2], pid);
			return (0);
		}
	}
	else
	{
		return (1);
	}
}

/*
	The string "msg" is translated into binary signals on a character-per-
	character basis. It only works for ASCII characters. These are encoded
	into 0's and 1's with the signal "SIGUSR1" representing 0 and "SIGUSR2"
	representing 1. At least 42 microseconds delay after each signal ensure
	that the server will be ready to receive the next signal.
*/
static void	snd_msg(char *msg, int pid)
{
	char	c;
	int		remainder;
	int		count;
	size_t	ndx;

		ndx = 0;
		c = msg[ndx];
	while (c)
	{
		count = 0;
		while (count < 7)
		{
			remainder = c % 2;
			if (remainder == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			c /= 2;
			count++;
			usleep(42);
		}
		ndx++;
		c = msg[ndx];
	}
}

/*
	A custom version of atoi that returns -42 if "str" contains alphabetical
	characters. Note that a pid of "-42" would be interpreted as an error in
	the main function.
*/
static int	ato_pid(const char *str)
{
	pid_t	result;
	size_t	ndx;
	size_t	start;

		result = 0;
		start = 0;
	while (str[start] == ' ' || str[start] == '\n' || str[start] == '\f'
		|| str[start] == '\r' || str[start] == '\t' || str[start] == '\v')
		start++;
	if (str[start] == '+' || str[start] == '-')
		start++;
	ndx = start;
	while (str[ndx] >= '0' && str[ndx] <= '9')
	{
		result *= 10;
		result += (int)(str[ndx] - '0');
		ndx++;
	}
	if (str[ndx] != '\0' || result == 0)
		return (-42);
	else if (start > 0 && str[start - 1] == '-')
		result *= -1;
	return (result);
}
