##
## EPITECH PROJECT, 2024
## B-FUN-400-STG-4-1-compressor-noe.tritsch
## File description:
## Makefile
##

BINARY_PATH	:=	$(shell stack path --local-install-root)

NAME	=	mypandoc

all:
	stack build
	cp $(BINARY_PATH)/bin/$(NAME)-exe ./$(NAME)

clean:
	stack clean

fclean:	clean
	rm -f $(NAME)

tests_run:
	stack test --coverage

re:	fclean all

.PHONY:	all clean fclean re tests_run
