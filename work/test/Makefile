
CC	= cc -Wall -Wextra -Werror -g -O3

NAME	= fractol
SRC	= src/control.c\
	  src/draw.c\
	  src/main.c\
	  src/utils.c\
	  src/event.c\

OBJ  = $(SRC:.c=.o)

all : $(NAME) 



$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "Compilation of $(NAME)"



%.o : %.c fractol.h
	@$(CC) -c $< -o $@

clean :
	@rm -rf $(OBJ)
	@echo "$(NAME) OBJS DELETED ✔️"

fclean : clean
	@rm -rf $(NAME)
	@echo "$(NAME) DELETED ✔️"

re : fclean all