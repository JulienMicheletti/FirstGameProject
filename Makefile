CC=		gcc

RM=		rm -rf *~

CFLAGS=		-lSDL -lSDL_image

NAME=		game

SRC=		main.c \
		game.c \
		sources.c 

OBJ=		$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
