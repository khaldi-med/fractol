
SRCS = ft_put_pointer.c ft_putstr.c ft_putchar.c\
   ft_putnbr_base.c ft_putnbr.c ft_printf.c

NAME = libftprintf.a


OBJ = $(SRCS:.c=.o)


CC = cc


FLAGS = -Wall -Wextra -Werror


all: $(NAME)


%.o: %.c ft_printf.h
	$(CC) $(FLAGS) -c $< -o $@


$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)


clean:
	rm -f $(OBJ)


fclean: clean
	rm -f $(NAME)


re: fclean all


.PHONY: all clean fclean re
