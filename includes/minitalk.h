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

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_server
{
	char	current_char;
	int		bit_count;
}	t_server;
void	send_bit(int bit, pid_t server_pid);
void	send_char(char c, pid_t server_pid);
void	sig_handler(int sig, siginfo_t *info, void *context);
void	setup_signal(void);
void	sig_acknowledge(int sig);

#endif
