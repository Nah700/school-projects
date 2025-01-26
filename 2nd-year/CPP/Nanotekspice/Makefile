##
## EPITECH PROJECT, 2024
## B-OOP-400-STG-4-1-tekspice-julien.dufaur
## File description:
## Makefile
##

SRC	=	main.cpp \
		Nanotekspice.cpp \
		Circuit.cpp \
		AComponent.cpp \
		parsing/main_error_handling.cpp \
		parsing/parse_chipset.cpp \
		parsing/parse_links.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	nanotekspice

CFLAGS += -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)
	find -name "*~" -delete -or -name "#*#" -delete

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
