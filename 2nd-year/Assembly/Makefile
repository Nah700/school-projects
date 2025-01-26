##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## je souis encore plus perdou que dabitude
##

SRC		=	strlen.asm \
			strchr.asm \
			strrchr.asm \
			memset.asm \
			memcpy.asm \
			strcmp.asm \
			strncmp.asm \
			strcasecmp.asm \
			strstr.asm \
			strpbrk.asm \
			strcspn.asm

TEST	=	main.c

OBJ		=	$(SRC:.asm=.o)

ASFLAGS	=	-f elf64

NAME	=	libasm.so

TEST_OBJ = $(TEST:.c=.o)

TEST_BINARY = mes_test

%.o: %.asm
		nasm $(ASFLAGS) -o $@ $<

all: $(NAME)

$(NAME): $(OBJ)
	ld -shared -o $(NAME) $(OBJ)

$(TEST_BINARY): CPPFLAGS += -fno-builtin
$(TEST_BINARY):
				gcc -o $(TEST_BINARY) $(TEST) -L. -lasm $(CPPFLAGS)
				export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

tests_run: $(TEST_BINARY)

clean:
	rm -f $(OBJ)
	rm -f $(TEST_OBJ)
	find -name "*~" -delete -or -name "#*#" -delete

fclean:	clean
	rm -f $(NAME)
	rm -f $(TEST_BINARY)

re: fclean all


.PHONY: all clean fclean re tests_run