/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:35:27 by yufli             #+#    #+#             */
/*   Updated: 2025/03/16 20:53:10 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

volatile t_state	g_state = {0};

int	is_valid_utf8(const char *buffer, int len)
{
	unsigned char	first;

	if (len == 0)
		return (0);
	first = buffer[0];
	if (first <= 0x7F)
		return (len == 1);
	if (first >= 0xC2 && first <= 0xDF)
		return (len == 2);
	if (first >= 0xE0 && first <= 0xEF)
		return (len == 3);
	if (first >= 0xF0 && first <= 0xF4)
		return (len == 4);
	return (0);
}

void	server_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_state.client_pid != info->si_pid)
	{
		g_state.client_pid = info->si_pid;
		g_state.current_byte = 0;
		g_state.bit_count = 0;
		g_state.byte_count = 0;
	}
	g_state.current_byte = (g_state.current_byte << 1) | (sig == SIGUSR2);
	g_state.bit_count++;
	if (g_state.bit_count == 8)
	{
		g_state.buffer[g_state.byte_count++] = g_state.current_byte;
		g_state.current_byte = 0;
		g_state.bit_count = 0;
		if (is_valid_utf8((const char *)g_state.buffer, g_state.byte_count))
		{
			write(1, (const void *)g_state.buffer, g_state.byte_count);
			g_state.byte_count = 0;
		}
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = server_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
