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
		sig = SIGUSR2; /* 如果 bit 为 1，发送 SIGUSR2 信号 */
	else
		sig = SIGUSR1; /* 如果 bit 为 0，发送 SIGUSR1 信号 */
	if (kill(server_pid, sig) == -1) /* 发送信号到服务器进程 */
	{
		write(2, "kill error\n", 11); /* 发送失败，输出错误信息 */
		exit(EXIT_FAILURE); /* 退出程序 */
	}
	usleep(500); /* 等待 500 微秒，确保信号被处理 */
}

void	send_char(char c, pid_t server_pid)
{
	int	i;
	i = 8;
	while (i--)
		send_bit((c >> i) & 1, server_pid); /* 逐位发送字符，从最高位到最低位 */
}

void	sig_acknowledge(int sig)
{
	(void)sig;
	ft_printf("Signal received by server\n"); /* 服务器确认收到信号 */
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	int	i;

	if (argc != 3) /* 检查命令行参数是否正确 */
	{
		ft_printf("Usage: ./client <server_pid> <message>\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]); /* 将 PID 字符串转换为整数 */
	if (server_pid <= 0) /* 检查 PID 是否有效 */
	{
		ft_printf("Invalid PID\n");
		return (1);
	}
	message = argv[2]; /* 获取要发送的消息 */
	signal(SIGUSR1, sig_acknowledge); /* 设置信号处理函数 */
	i = 0;
	while (message[i])
		send_char(message[i++], server_pid); /* 逐个字符发送消息 */
	send_char('\0', server_pid); /* 发送终止符 */
	return (EXIT_SUCCESS);
}