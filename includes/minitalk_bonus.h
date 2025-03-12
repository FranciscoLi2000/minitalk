#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_state
{
	sig_atomic_t	current_bit;
	sig_atomic_t	current_char;
	char			*buffer;
	size_t			buff_size;
	size_t			index;
}	t_state;

volatile t_state	g_state;

void	init_state(void);
void	handle_char(void);
void	signal_handler(int sig, siginfo_t *info, void *ctx);
void	send_char(pid_t pid, char c);

#endif
