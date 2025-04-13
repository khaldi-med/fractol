# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 18:45:26 by mohkhald          #+#    #+#              #
#    Updated: 2025/04/13 16:40:12 by mohkhald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = fractol

# Source files
SRCS = fractol.c render.c events.c complex.c color.c utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
MLX_DIR = ../mlx
LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf

# Libraries
MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# Include directories
INCLUDES = -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

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
$(NAME): $(MLX) $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) \
		-L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf $(MLX_FLAGS)
	@echo "\033[0;32mFractol compiled successfully!\033[0m"

# Compile mlx
$(MLX):
	@echo "\033[0;33mCompiling MLX...\033[0m"
	@make -C $(MLX_DIR)
	@echo "\033[0;32mMLX compiled successfully!\033[0m"
# Compile libft
$(LIBFT):
	@echo "\033[0;33mCompiling libft...\033[0m"
	@make -C $(LIBFT_DIR)
	@echo "\033[0;32mLibft compiled successfully!\033[0m"

# Compile ft_printf
$(FT_PRINTF):
	@echo "\033[0;33mCompiling ft_printf...\033[0m"
	@make -C $(FT_PRINTF_DIR)
	@echo "\033[0;32mft_printf compiled successfully!\033[0m"

# Rule to compile .c to .o
%.o: %.c draw.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "\033[0;33mCleaning object files...\033[0m"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
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
