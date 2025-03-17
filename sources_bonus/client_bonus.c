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
	(void)sig; /* 忽略参数 sig */
	(void)info; /* 忽略参数 info */
	(void)context; /* 忽略参数 context */
}

void	send_byte(char byte, pid_t server_pid)
{
	struct sigaction	sa;
	int				i;
	int				signal;

	sa.sa_sigaction = ack_handler; /* 设置信号处理函数 */
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask); /* 清空信号掩码集 */
	sigaction(SIGUSR1, &sa, NULL); /* 绑定 SIGUSR1 信号处理函数 */
	i = 8;
	while (i--)
	{
		if ((byte >> i) & 1) /* 判断当前位是 1 还是 0 */
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		if (kill(server_pid, signal) == -1) /* 发送信号到服务器 */
		{
			write(2, "kill error\n", 11); /* 发送失败，输出错误信息 */
			exit(EXIT_FAILURE); /* 退出程序 */
		}
		pause(); /* 等待服务器的确认信号 */
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	size_t	i;

	if (argc != 3) /* 检查参数数量是否正确 */
	{
		ft_printf("Usage: ./client_bonus <server_pid> <message>\n");
		exit(EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]); /* 将 PID 字符串转换为整数 */
	if (server_pid <= 0) /* 检查 PID 是否有效 */
	{
		ft_printf("Invalid PID\n");
		exit(EXIT_FAILURE);
	}
	message = argv[2]; /* 获取要发送的消息 */
	i = 0;
	while (message[i])
		send_byte(message[i++], server_pid); /* 逐字节发送消息 */
	send_byte('\0', server_pid); /* 发送终止符号 */
	return (0);
}