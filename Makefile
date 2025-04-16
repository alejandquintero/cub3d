# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/08 10:37:13 by aquinter          #+#    #+#              #
#    Updated: 2025/03/22 16:57:23 by aquinter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

RED		= \033[0;31m
GREEN	= \033[0;32m
NC		= \033[0m

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
DFLAG	= -g3 -fsanitize=address
RM		= rm -f

LIBFT	= libft_v2/libft_v2.a
LIBFT_PATH	= libft_v2/

MLX42	= MLX42/build/libmlx42.a
MLX42_PATH	= MLX42/

SRC_DIR		= src/

SRCS	= $(addprefix $(SRC_DIR), 	\
	main.c							\
	init.c							\
	free.c							\
	parsing/parser.c				\
	parsing/checker.c				\
	parsing/extractor.c				\
	parsing/maze.c					\
	parsing/chars.c					\
	parsing/llist.c					\
	parsing/print_utils.c			\
	raycasting/window.c				\
	raycasting/hooks.c				\
	raycasting/render.c				\
	raycasting/render_utils.c		\
	raycasting/raycasting.c			\
	raycasting/movements.c			\
	raycasting/mouse.c				\
	)

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make $(MAKECMDGOALS) -sC $(LIBFT_PATH)
	
	@echo "$(GREEN)Compiling MLX42 library...$(NC)"
	@cmake $(MLX42_PATH) -B $(MLX42_PATH)/build 1>/dev/null
	@make -C $(MLX42_PATH)/build -j4 1>/dev/null
	
	@echo "$(GREEN)Compiling cub3D...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) \
		-I inc $(MLX42) -ldl -lglfw -pthread -lm $(LIBFT) -o $(NAME)
	
	@echo "$(GREEN)Enjoy!$(NC)"

debug: CFLAGS += $(DFLAG)
debug: $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(MLX42_PATH)/build
	@echo "$(RED)All objs deleted.$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "$(RED)Everything deleted.$(NC)"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
