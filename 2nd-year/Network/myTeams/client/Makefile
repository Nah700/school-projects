##
## EPITECH PROJECT, 2024
## B-NWP-400-STG-4-1-myftp-julien.dufaur
## File description:
## Makefile
##

CFLAGS 	+= 	-Wall -Wextra -g -I./include -L../libs/myteams/ -lmyteams

SRC     =	src/main.c \
			src/args_parsing.c \
			src/client/client.c \
			src/client/core/core.c \
			src/client/core/receive.c \
			src/client/core/utils.c \
			src/client/core/loop.c \
			src/client/core/print/print_a.c \
			src/client/core/print/print_b.c \
			src/client/core/print/print_c.c \
			../commons/utils.c \
			../commons/string.c \

OBJ     =   $(SRC:.c=.o)

NAME    =	myteams_cli

all:    $(NAME)

$(NAME):    $(OBJ)
		gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		find . -name '*.o' -delete
		find ../commons -name '*.o' -delete
		find . -name '*~' -delete
		find . -name '#*#' -delete
		find . -name '*.a' -delete
		find . -name 'vgcore.*' -delete
		find . -name 'coding-style-reports.log' -delete

fclean: clean
		rm -f $(NAME)
		rm -f test

re:		fclean all

.PHONY: all clean fclean re
