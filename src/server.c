#include "minitalk.h"

/* 辅助函数：初始化全局变量 */
static void	init_state(void)
{
	g_state.buff_size = BUFFER_SIZE;
	g_state.buffer = malloc(g_state.buff_size);
	if (!g_state.buffer)
	{
		write(2, "Error: malloc failed\n", 20);
		exit(1);
	}
	g_state.index = 0;
	g_state.current_bit = 0;
	g_state.current_char = 0;
}
/* 全局变量：动态缓冲区、当前缓冲区大小和已写入字符的下标 */
/* 用于重建当前字符的变量：当前已接收的位数以及当前字符 */

/* 当消息接收完成（收到'\0'）后，打印消息并重置缓冲区 
static void	handle_complete_message(void)
{
	 为了安全起见，先在缓冲区末尾加上终止符 
	t_state.buffer[t_state.index] = '\0';
	write(1, t_state.buffer, t_state.index);
	write(1, "\n", 1);
	 重置缓冲区下标（保留已分配的内存，下次继续使用）
	t_state.index = 0;
	 可选：重置缓冲区内存（更严格的内存管理）
	ft_memset(t_state.buffer, 0, t_state.buff_size);
}*/

/* 辅助函数：处理字符组装和缓冲区扩展 */
void	handle_char(void)
{
	char	*tmp;

	if (g_state.current_char == '\0')
	{
		write(1, "Received message: ", 18);
		write(1, g_state.buffer, g_state.index);
		write(1, "\n", 1);
		g_state.index = 0;
	}
	else
	{
		if (g_state.index + 1 >= g_state.buff_size)
		{
			g_state.buff_size += 1024;
			tmp = realloc(g_state.buffer, g_state.buff_size);
			if (!tmp)
			{
				g_state.buffer = tmp;
				write(2, "Error\n", 6);
				exit(1);
			}
			g_state.buffer[g_state.index++] = g_state.current_char;
		}
		g_state.current_bit = 0;
		g_state.current_char = 0;
	}
}

/* 信号处理函数（25行以内）*/
void	signal_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;

	/* 假设：SIGUSR1 代表 1，SIGUSR2 代表 0 */
	if (sig == SIGUSR1)
		g_state.current_char |= (1 << (7 - g_state.current_bit));
	/* SIGUSR2 对应的位默认为0，无需额外操作 */
	/* 当接收到8个位后，构成一个完整字符 */
	g_state.current_bit++;
	if (g_state.current_bit == 8)
		handle_char();
}

int	main(void)
{
	struct sigaction	sa;

	/* 初始化动态缓冲区 */
	init_state();
	/* 配置信号处理 */
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask); /* 清空信号掩码 */
	/* ft_memset(g_buffer, 0, g_buff_size);
	 启动时显示服务器 PID 
	pid = getpid();
	ft_printf("Server started. PID: %d\n", pid);
	 配置 sigaction，设置对 SIGUSR1 和 SIGUSR2 的处理函数
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO; */
	/* 启用 sa_sigaction 字段 */
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		exit(1);
	}
	ft_printf("Server PID: %d\n", getpid());
	/* 主循环：不断等待信号 */
	while (1)
		pause();
	free(g_state.buffer);
	return (0);
}
