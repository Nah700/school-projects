##
## EPITECH PROJECT, 2024
## B-NWP-400-STG-4-1-myftp-julien.dufaur
## File description:
## Makefile
##

.SILENT:

CFLAGS 	+= 	-Wall -Wextra -g -I./include -luuid -L../libs/myteams/ -lmyteams

SRC     =	src/main.c \
			src/args_parsing.c \
			src/server/server_handling.c \
			src/server/myteams.c \
			src/server/client_handling.c \
			src/server/commands.c \
			src/teams/teams.c \
			src/server/commands/list.c \
			src/server/commands/create.c \
			src/teams/team.c \
			src/server/commands/info.c \
			../commons/utils.c \
			../commons/string.c \
			src/server/commands/use.c \
			src/teams/channel.c \
			src/teams/thread.c \
			src/teams/comment.c \
			src/server/database/users.c \
			src/server/database/private_msgs.c \
			src/server/database/utils.c \
			src/server/database/user_register_chan.c \
			src/server/utilities_commands.c \
			src/server/answer.c \
			src/server/commands/subscribe.c \
			src/server/commands/message.c \
			src/server/commands/login.c \
			src/server/exist_handler.c \
			src/server/utils.c \
			src/server/commands/print.c \

OBJ     =   $(SRC:.c=.o)

NAME    =	myteams_server

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
