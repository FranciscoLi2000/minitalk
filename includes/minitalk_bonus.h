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

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct state
{
	pid_t	client_pid;
	char	current_byte;
	char	buffer[4];
	int		bit_count;
	int		byte_count;
}	t_state;
void	ack_handler(int sig, siginfo_t *info, void *context);
void	send_byte(char byte, pid_t server_pid);
void	server_handler(int sig, siginfo_t *info, void *context);
int		is_valid_utf8(const char *buffer, int len);

#endif
