##
## EPITECH PROJECT, 2024
## B-NWP-400-STG-4-1-myteams-julien.dufaur
## File description:
## Makefile
##

CLIENT   =	myteams_cli
SERVER   =	myteams_server

all:	myteams

myteams:
		make -C client
		make -C server
		mv client/$(CLIENT) .
		mv server/$(SERVER) .

clean:
		find . -name '*.o' -delete
		find . -name '*~' -delete
		find . -name '#*#' -delete
		find . -name '*.a' -delete
		find . -name 'vgcore.*' -delete
		find . -name 'coding-style-reports.log' -delete

fclean: clean
		rm -f $(CLIENT)
		rm -f $(SERVER)
		rm -f test

re:		fclean all

.PHONY: all clean fclean re
