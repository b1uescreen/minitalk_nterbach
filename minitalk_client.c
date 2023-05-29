#include <signal.h>
#include <unistd.h>

static void	snd_msg(char *msg, int pid);
static int	ato_pid(const char *str);

/*
	arg0 is the path to the executable
	arg1 shall be the server PID
	arg2 shall be the string to be sent
*/
int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc == 3 && argv[2] != NULL)
	{
		pid = ato_pid(argv[1]);
		snd_msg(argv[2], pid);
	}
	return (0);
}

static void	snd_msg(char *msg, int pid)
{
	char	c;
	int		remainder;
	int 	count;
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
		usleep(42);
	}
}

static int	scout(const char *str)
{
	size_t	ndx;

	ndx = 0;
	while (str[ndx] == ' ' || str[ndx] == '\n' || str[ndx] == '\f'
		|| str[ndx] == '\r' || str[ndx] == '\t' || str[ndx] == '\v')
		ndx++;
	if (str[ndx] == '+' || str[ndx] == '-')
		ndx++;
	return (ndx);
}

static int	ato_pid(const char *str)
{
	pid_t	result;
	size_t	ndx;
	size_t	start;

		result = 0;
		start = scout(str);
		ndx = start;
	while (str[ndx] >= '0' && str[ndx] <= '9')
	{
		result *= 10;
		result += (int)(str[ndx] - '0');
		ndx++;
	}
	if (start > 0 && str[start - 1] == '-')
		result *= -1;
	return (result);
}
