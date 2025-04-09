# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 18:45:26 by mohkhald          #+#    #+#              #
#    Updated: 2025/04/08 18:45:26 by mohkhald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = fractol

# Source files
SRCS = main.c fractal_render.c events.c utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf
MLX_DIR = ./mlx

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
MLX = $(MLX_DIR)/libmlx.a

# Include directories
INCLUDES = -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(MLX_DIR)

# Platform detection
UNAME := $(shell uname)

# Platform-specific settings
ifeq ($(UNAME), Darwin)
	# macOS
	MLX_FLAGS = -framework OpenGL -framework AppKit
else
	# Linux
	MLX_FLAGS = -lXext -lX11 -lm -lz
endif

# Default target
all: $(NAME)

# Rule to make the executable
$(NAME): $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) \
		-L$(LIBFT_DIR) -lft \
		-L$(FT_PRINTF_DIR) -lftprintf \
		-L$(MLX_DIR) -lmlx $(MLX_FLAGS)
	@echo "\033[0;32mFractol compiled successfully!\033[0m"
	@echo "Usage: ./fractol [mandelbrot/julia] [parameters]"

# Compile libft
$(LIBFT):
	@echo "\033[0;33mCompiling libft...\033[0m"
	@make -C $(LIBFT_DIR)
	@echo "\033[0;32mLibft compiled successfully!\033[0m"

# Compile ft_printf
$(FT_PRINTF):
	@echo "\033[0;33mCompiling ft_printf...\033[0m"
	@make -C $(FT_PRINTF_DIR)
	@echo "\033[0;32mFt_printf compiled successfully!\033[0m"

# Compile mlx
$(MLX):
	@echo "\033[0;33mCompiling MLX...\033[0m"
	@make -C $(MLX_DIR)
	@echo "\033[0;32mMLX compiled successfully!\033[0m"

# Rule to compile .c to .o
%.o: %.c fractol.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "\033[0;33mCleaning object files...\033[0m"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "\033[0;32mCleaned object files!\033[0m"

# Clean object files and executable
fclean: clean
	@echo "\033[0;33mCleaning executable...\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@echo "\033[0;32mCleaned executable!\033[0m"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
