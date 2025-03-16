/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:41:25 by yufli             #+#    #+#             */
/*   Updated: 2025/03/16 19:35:14 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_bit(int bit, pid_t server_pid)
{
	int	sig;

	if (bit)
		sig = SIGUSR2;
	else
		sig = SIGUSR1;
	if (kill(server_pid, sig) == -1)
	{
		write(2, "kill error\n", 11);
		exit(EXIT_FAILURE);
	}
	usleep(500);
}

void	send_char(char c, pid_t server_pid)
{
	int	i;

	i = 8;
	while (i--)
		send_bit((c >> i) & 1, server_pid);
}

void	sig_acknowledge(int sig)
{
	(void)sig;
	ft_printf("Signal received by server\n");
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_printf("Usage: ./client <server_pid> <message>\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Invalid PID\n");
		return (1);
	}
	message = argv[2];
	signal(SIGUSR1, sig_acknowledge);
	i = 0;
	while (message[i])
		send_char(message[i++], server_pid);
	send_char('\0', server_pid);
	return (EXIT_SUCCESS);
}
