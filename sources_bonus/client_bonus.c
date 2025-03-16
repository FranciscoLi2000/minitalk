/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:08:02 by yufli             #+#    #+#             */
/*   Updated: 2025/03/16 20:17:22 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	ack_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
}

void	send_byte(char byte, pid_t server_pid)
{
	struct sigaction	sa;
	int					i;
	int					signal;

	sa.sa_sigaction = ack_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	i = 8;
	while (i--)
	{
		if ((byte >> i) & 1)
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		if (kill(server_pid, signal) == -1)
		{
			write(2, "kill error\n", 11);
			exit(EXIT_FAILURE);
		}
		pause();
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	size_t	i;

	if (argc != 3)
	{
		ft_printf("Usage: ./client_bonus <server_pid> <message>\n");
		exit(EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Invalid PID\n");
		exit(EXIT_FAILURE);
	}
	message = argv[2];
	i = 0;
	while (message[i])
		send_byte(message[i++], server_pid);
	send_byte('\0', server_pid);
	return (0);
}
