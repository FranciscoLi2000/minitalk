# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yufli <yufli@student.42barcelona.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 15:19:46 by yufli             #+#    #+#              #
#    Updated: 2025/03/16 20:32:36 by yufli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER = server
NAME_SERVER_BONUS = server_bonus

SRCDIR = sources
BONUSDIR = sources_bonus
INCDIR = includes
LIBFTDIR = libft

CLIENT_SRCS = $(SRCDIR)/client.c
CLIENT_SRCS_BONUS = $(BONUSDIR)/client_bonus.c
SERVER_SRCS = $(SRCDIR)/server.c
SERVER_SRCS_BONUS = $(BONUSDIR)/server_bonus.c

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CLIENT_OBJS_BONUS = $(CLIENT_SRCS_BONUS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
SERVER_OBJS_BONUS = $(SERVER_SRCS_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIBFTDIR)/libft.a

all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	@make -C $(LIBFTDIR)

$(NAME_CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCDIR) $(CLIENT_OBJS) -L$(LIBFTDIR) -lft -o $(NAME_CLIENT)

$(NAME_CLIENT_BONUS): $(CLIENT_OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCDIR) $(CLIENT_OBJS_BONUS) -L$(LIBFTDIR) -lft -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCDIR) $(SERVER_OBJS) -L$(LIBFTDIR) -lft -o $(NAME_SERVER)

$(NAME_SERVER_BONUS): $(SERVER_OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCDIR) $(SERVER_OBJS_BONUS) -L$(LIBFTDIR) -lft -o $(NAME_SERVER_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

bonus: $(LIBFT) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS_BONUS) $(SERVER_OBJS_BONUS)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
