# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 22:36:12 by mohkhald          #+#    #+#              #
#    Updated: 2025/04/17 22:50:17 by mohkhald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = fractal

SRCS = main.c init.c render.c math.c events.c parse.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = ./minilibx
LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf

MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

%.o: %.c fractal.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MLX) $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(MLX) $(LIBFT) $(FT_PRINTF) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX):
	@make -C $(MLX_DIR)
	@echo "\033[0;32mMLX compiled successfully!\033[0m"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "\033[0;32mLibft compiled successfully!\033[0m"

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)
	@echo "\033[0;32mft_printf compiled successfully!\033[0m"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@echo "\033[0;32mCleaned object files!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@echo "\033[0;32mCleaned executable!\033[0m"

re: fclean all

.PHONY: all clean fclean re
