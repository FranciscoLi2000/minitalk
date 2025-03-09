#include "minitalk.h"

/* 辅助函数：检查PID是否为有效正整数 */
static int	is_valid_pid(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/* 发送一个字符的8个二进制位（从高位到低位）*/
static void	send_char(pid_t pid, char c)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1; /* 提取第 i 位 */
		if (bit == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				/* 发送 SIGUSR1 表示 0 */
				write(2, "Error: kill failed\n", 19);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				/* 发送 SIGUSR2 表示 1 */
				write(2, "Error: kill failed\n", 19);
				exit(1);
			}
		}
		usleep(100); /* 延迟，避免信号丢失 */
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	size_t	i;

	/* 1. 参数合法性检查 */
	if (argc != 3)
	{
		write(2, "Usage: ./client <server_pid> <message>\n", 39);
		exit(1);
	}
	/* 2. 验证PID是否为有效数字 */
	if (!is_valid_pid(argv[1]))
	{
		write(2, "Error: Invalid PID format\n", 26);
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		write(2, "Error: PID must be a positive integer\n", 38);
		exit(1);
	}
	/* 3. 遍历字符串的每个字符（包括终止符'\0'）*/
	message = argv[2];
	i = 0;
	while (i <= (size_t)ft_strlen(message))
	{
		send_char(server_pid, message[i]);
		i++;
	}
	return (0);
}
