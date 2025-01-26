##
## EPITECH PROJECT, 2024
## B-FUN-400-STG-4-1-compressor-nahim.kandari
## File description:
## Makefile
##

NAME	=	imageCompressor

all:	$(NAME)

$(NAME):
	stack build
	cp $(shell stack path --local-install-root)/bin/$(NAME)-exe ./$(NAME)

clean:
	stack clean

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
