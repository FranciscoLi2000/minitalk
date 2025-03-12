#include "../includes/minitalk.h"

void	handle_char(void)
{
	char	*new_buff;
	size_t	new_size;

	if (g_state.current_char == '\0')
	{
		write(1, g_state.buffer, g_state.index);
		write(1, "\n", 1 * (g_state.index > 0));
		g_state.index = 0;
	}
	else if (++g_state.index >= g_state.buff_size)
	{
		new_size = g_state.buff_size + 1024;
		new_buff = malloc(new_size);
		if (!new_buff)
			exit_error("Error: malloc failed\n");
		ft_memcpy(new_buff, g_state.buffer, g_state.buff_size);
		free(g_state.buffer);
		g_state.buffer = new_buff;
		g_state.buff_size = new_size;
	}
	else
		g_state.buffer[g_state.index - 1] = g_state.current_char;
	g_state.current_bit = 0;
	g_state.current_char = 0;
}

void	signal_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (sig == SIGUSR1)
		g_state.current_char |= (1 << (7 - g_state.current_bit));
	g_state.current_bit++;
	if (g_state.current_bit == 8)
		handle_char();
}

int	main(void)
{
	struct sigaction	sa;

	init_state();
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit_error("Error: sigaction failed\n");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
