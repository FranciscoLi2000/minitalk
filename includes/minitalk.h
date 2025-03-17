/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:04:12 by yufli             #+#    #+#             */
/*   Updated: 2025/03/16 19:35:57 by yufli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h> /* 引入 signal 库，用于处理信号 */
# include <unistd.h> /* 引入 unistd.h，提供系统调用函数 */
# include <stdlib.h> /* 引入 stdlib.h，提供内存管理、转换和进程控制函数 */
# include "../libft/libft.h" /* 引入 libft 头文件，提供额外的实用函数 */

typedef struct s_server
{
	char	current_char; /* 存储当前接收的字符 */
	int	bit_count; /* 记录接收的比特位数 */
} t_server;

void	send_bit(int bit, pid_t server_pid); /* 发送单个位信号 */
void	send_char(char c, pid_t server_pid); /* 发送整个字符 */
void	sig_handler(int sig, siginfo_t *info, void *context); /* 处理接收到的信号 */
void	setup_signal(void); /* 设置信号处理函数 */
void	sig_acknowledge(int sig); /* 服务器确认收到信号 */

#endif