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

static t_server	g_data = {0}; /* 定义全局变量存储接收到的数据 */

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_data.current_char = (g_data.current_char << 1) | (sig == SIGUSR2); /* 通过位移接收字符的每一位 */
	g_data.bit_count++;
	if (g_data.bit_count == 8) /* 当接收满 8 位时 */
	{
		if (g_data.current_char == '\0') /* 如果接收到的是终止符 */
		{
			write(1, "\n", 1); /* 输出换行 */
			kill(info->si_pid, SIGUSR1); /* 发送确认信号给客户端 */
		}
		else
			write(1, &g_data.current_char, 1); /* 输出接收到的字符 */
		g_data.bit_count = 0; /* 重置 bit 计数器 */
		g_data.current_char = 0; /* 重置当前字符 */
	}
	kill(info->si_pid, SIGUSR1); /* 发送确认信号给客户端 */
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler; /* 设置信号处理函数 */
	sa.sa_flags = SA_SIGINFO; /* 允许获取更多信号信息 */
	sigemptyset(&sa.sa_mask); /* 清空信号集 */
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1) /* 绑定信号处理函数 */
	{
		write(2, "Signal error\n", 13); /* 发生错误，输出错误信息 */
		exit(EXIT_FAILURE); /* 退出程序 */
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid()); /* 输出服务器的进程 ID */
	setup_signal(); /* 设置信号处理 */
	while (1)
		pause(); /* 让服务器一直等待信号 */
	return (0);
}