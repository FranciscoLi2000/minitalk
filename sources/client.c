#include "../includes/minitalk.h"

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	size_t	i;

	if (argc != 3)
		exit_error("Usage: ./client <server_pid> <message>\n");
	if (!is_valid_pid(argv[1]))
		exit_error("Error: Invalid PID format\n");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		exit_error("Error: Invalid PID\n");
	message = argv[2];
	i = 0;
	while (i <= (size_t)ft_strlen(message))
	{
		send_char(server_pid, message[i]);
		i++;
	}
	return (0);
}