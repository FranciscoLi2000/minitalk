NAME_CLIENT		= client
NAME_SERVER		= server
NAME_CLIENT_BONUS	= client_bonus
NAME_SERVER_BONUS	= server_bonus

CC			= cc
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -I includes -I libft

SRC_DIR			= src
LIBFT_DIR		= libft
OBJ_DIR			= obj

LIBFT			= $(LIBFT_DIR)/libft.a

CLIENT_SRC		= $(SRC_DIR)/client.c
SERVER_SRC		= $(SRC_DIR)/server.c
CLIENT_BONUS_SRC	= $(SRC_DIR)/client_bonus.c
SERVER_BONUS_SRC	= $(SRC_DIR)/server_bonus.c

CLIENT_OBJ		= $(CLIENT_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SERVER_OBJ		= $(SERVER_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CLIENT_BONUS_OBJ	= $(CLIENT_BONUS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SERVER_BONUS_OBJ	= $(SERVER_BONUS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

bonus: $(LIBFT) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME_CLIENT): $(CLIENT_OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(LIBFT_DIR) -lft

$(NAME_SERVER): $(SERVER_OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(LIBFT_DIR) -lft

$(NAME_CLIENT_BONUS): $(CLIENT_BONUS_OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(LIBFT_DIR) -lft

$(NAME_SERVER_BONUS): $(SERVER_BONUS_OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(LIBFT_DIR) -lft

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
