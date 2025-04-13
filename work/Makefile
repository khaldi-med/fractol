# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 18:45:26 by mohkhald          #+#    #+#              #
#    Updated: 2025/04/13 02:29:17 by mohkhald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = color

# Source files
SRCS = draw.c utils.c
# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
MLX_DIR = ../mlx

# Libraries
MLX = $(MLX_DIR)/libmlx.a

# Include directories
INCLUDES = -I. -I$(MLX_DIR)

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
$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) \
		-L$(MLX_DIR) -lmlx $(MLX_FLAGS)
	@echo "\033[0;32mFractol compiled successfully!\033[0m"
	@echo "Usage: ./fractol [mandelbrot/julia] [parameters]"

# Compile mlx
$(MLX):
	@echo "\033[0;33mCompiling MLX...\033[0m"
	@make -C $(MLX_DIR)
	@echo "\033[0;32mMLX compiled successfully!\033[0m"

# Rule to compile .c to .o
%.o: %.c draw.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "\033[0;33mCleaning object files...\033[0m"
	@make -C $(MLX_DIR) clean
	@echo "\033[0;32mCleaned object files!\033[0m"

# Clean object files and executable
fclean: clean
	@echo "\033[0;33mCleaning executable...\033[0m"
	@rm -f $(NAME)
	@echo "\033[0;32mCleaned executable!\033[0m"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
