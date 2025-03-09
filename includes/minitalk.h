#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

/* 服务器全局状态结构体（符合单全局变量要求）*/
typedef struct	s_state
{
	char	*buffer;
	size_t	buff_size;
	size_t	index;
	sig_atomic_t	current_bit;
	sig_atomic_t	current_char;
}	t_state;
/* 函数声明 */
void	signal_handler(int sig, siginfo_t *info, void *ctx);
void	handle_char(void);
volatile t_state	g_state;

#endif
