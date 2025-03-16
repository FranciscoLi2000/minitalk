/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:48:38 by yufli             #+#    #+#             */
/*   Updated: 2025/03/16 19:13:09 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_server	g_data = {0};

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_data.current_char = (g_data.current_char << 1) | (sig == SIGUSR2);
	g_data.bit_count++;
	if (g_data.bit_count == 8)
	{
		if (g_data.current_char == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		else
			write(1, &g_data.current_char, 1);
		g_data.bit_count = 0;
		g_data.current_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Signal error\n", 13);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	setup_signal();
	while (1)
		pause();
	return (0);
}
