# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Name of the executable
NAME = fractol

# Source files
SRCS = main.c init.c render.c math.c events.c

# Object files
OBJS = $(SRCS:.c=.o)

# Directories
MLX_DIR = ./minilibx
LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf

# Libraries
MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# Include directories
INCLUDES = -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

LIB_FLAGS = -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Default target
all: $(NAME)

# Rule to make the executable
$(NAME): $(MLX) $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB_FLAGS) $(MLX_FLAGS) -o $(NAME)

# Compile mlx
$(MLX):
	@make -C $(MLX_DIR)
	@echo "\033[0;32mMLX compiled successfully!\033[0m"

# Compile libft
$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "\033[0;32mLibft compiled successfully!\033[0m"

# Compile ft_printf
$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)
	@echo "\033[0;32mft_printf compiled successfully!\033[0m"

# Rule to compile .c to .o
%.o: %.c fractal.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@echo "\033[0;32mCleaned object files!\033[0m"

# Clean object files and executable
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@echo "\033[0;32mCleaned executable!\033[0m"

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
