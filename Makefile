
CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = fractol

SRCS = parse.c main.c init.c render.c math.c events.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = ./mlx
LIBFT_DIR = ./libft
FT_PRINTF_DIR = ./ft_printf

MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

INCLUDES = -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

LIB_FLAGS = -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf
# Linux MLX flags
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB_FLAGS) $(MLX_FLAGS) -o $(NAME)

$(MLX):
	@make -C $(MLX_DIR)
	@echo "\033[0;32mMLX compiled successfully!\033[0m"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "\033[0;32mLibft compiled successfully!\033[0m"

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)
	@echo "\033[0;32mft_printf compiled successfully!\033[0m"

%.o: %.c fractal.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@echo "\033[0;32mCleaned object files!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@echo "\033[0;32mCleaned executable!\033[0m"

re: fclean all

.PHONY: all clean fclean re
