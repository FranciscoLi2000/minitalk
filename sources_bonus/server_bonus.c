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

volatile t_state	g_state = {0}; /* 定义全局状态变量 */

int	is_valid_utf8(const char *buffer, int len)
{
	unsigned char	first;

	if (len == 0)
		return (0);
	first = buffer[0];
	if (first <= 0x7F) /* 单字节 UTF-8 */
		return (len == 1);
	if (first >= 0xC2 && first <= 0xDF) /* 两字节 UTF-8 */
		return (len == 2);
	if (first >= 0xE0 && first <= 0xEF) /* 三字节 UTF-8 */
		return (len == 3);
	if (first >= 0xF0 && first <= 0xF4) /* 四字节 UTF-8 */
		return (len == 4);
	return (0);
}

void	server_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_state.client_pid != info->si_pid) /* 如果收到客户端的信号 */
	{
		g_state.client_pid = info->si_pid;
		g_state.current_byte = 0;
		g_state.bit_count = 0;
		g_state.byte_count = 0;
	}
	g_state.current_byte = (g_state.current_byte << 1) | (sig == SIGUSR2); /* 逐位接收数据 */
	g_state.bit_count++;
	if (g_state.bit_count == 8) /* 当收到 8 位时 */
	{
		g_state.buffer[g_state.byte_count++] = g_state.current_byte; /* 存入缓冲区 */
		g_state.current_byte = 0;
		g_state.bit_count = 0;
		if (is_valid_utf8((const char *)g_state.buffer, g_state.byte_count)) /* 检查是否是有效的 UTF-8 */
		{
			write(1, (const void *)g_state.buffer, g_state.byte_count); /* 输出 UTF-8 字符 */
			g_state.byte_count = 0;
		}
	}
	kill(info->si_pid, SIGUSR1); /* 发送确认信号 */
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = server_handler; /* 设置信号处理函数 */
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask); /* 清空信号集 */
	sigaction(SIGUSR1, &sa, NULL); /* 绑定 SIGUSR1 信号处理 */
	sigaction(SIGUSR2, &sa, NULL); /* 绑定 SIGUSR2 信号处理 */
	ft_printf("Server PID: %d\n", getpid()); /* 输出服务器的进程 ID */
	while (1)
		pause(); /* 让服务器一直等待信号 */
	return (0);
}