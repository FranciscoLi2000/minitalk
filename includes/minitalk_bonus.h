/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:12:40 by yufli             #+#    #+#             */
/*   Updated: 2025/03/16 20:33:37 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h> /* 引入 signal 头文件，处理信号 */
# include <stdlib.h> /* 引入 stdlib 头文件，提供通用工具函数 */
# include <unistd.h> /* 引入 unistd 头文件，提供系统调用功能 */
# include "../libft/libft.h" /* 引入 libft 头文件，提供额外的功能 */

typedef struct state
{
	pid_t	client_pid; /* 存储客户端的进程 ID */
	char	current_byte; /* 当前正在接收的字节 */
	char	buffer[4]; /* 缓冲区，存储接收的字节 */
	int	bit_count; /* 当前字节的位计数 */
	int	byte_count; /* 缓冲区中字节的计数 */
} t_state;

void	ack_handler(int sig, siginfo_t *info, void *context); /* 处理确认信号 */
void	send_byte(char byte, pid_t server_pid); /* 发送一个字节 */
void	server_handler(int sig, siginfo_t *info, void *context); /* 服务器信号处理函数 */
int	is_valid_utf8(const char *buffer, int len); /* 检查是否是有效的 UTF-8 编码 */

#endif