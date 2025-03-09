CC = cc
CFLAGS = -Wall -Werror -Wextra
CLIENT = client
SERVER = server
SRCS_CLIENT = src/client.c
SRCS_SERVER = src/server.c
INCLUDES = -I includes -I libft
LIBFT = libft/libft.a

all: $(LIBFT) $(CLIENT) $(SERVER)

$(LIBFT):
	@make -C libft

$(CLIENT): $(SRCS_CLIENT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L libft -lft

$(SERVER): $(SRCS_SERVER)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L libft -lft

clean:
	rm -f $(CLIENT) $(SERVER)
	@make -C libft clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
