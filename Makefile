FILES = main.c commande.c utils.c

SRC = $(addprefix src/, $(FILES))

CC = gcc

CFLAGS = -Werror

OBJ = $(SRC:.c=.o)

NAME = main

RM = rm -f

all:		$(NAME)

$(NAME): 	$(OBJ)
	@$(CC) $+ -o $@

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
