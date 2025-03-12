#include "../includes/minitalk.h"

/*void	exit_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	free(g_state.buffer);
	exit(1);
}*/
void	exit_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

int	is_valid_pid(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	send_char(pid_t pid, char c)
{
	int	i;
	int	bit;
	int	signal;

	i = 8;
	while (i--)
	{
		bit = (c >> i) & 1;
		if (bit)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		if (kill(pid, signal) == -1)
			exit_error("Error: kill failed\n");
		usleep(800);
	}
}

void	init_state(void)
{
	g_state.buffer = malloc(BUFFER_SIZE);
	if (!g_state.buffer)
	{
		write(2, "Error: malloc failed\n", 20);
		exit(1);
	}
	g_state.buff_size = BUFFER_SIZE;
	g_state.index = 0;
	g_state.current_bit = 0;
	g_state.current_char = 0;
}