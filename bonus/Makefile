##
## EPITECH PROJECT, 2019
## makefile
## File description:
## project makefile
##

SRC	=	src/main.c	\
		src/my_radar.c	\
		src/usage.c	\
		src/clock.c	\
		src/map.c	\
		src/draw.c	\
		src/check_planes.c	\
		src/planes_time.c	\
		src/planes.c	\
		src/destroy.c	\
		src/collisions.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CFLAGS	+=	-I include -Wall -Wextra
LDFLAGS +=	-L lib/my -lmy -L lib/graph -lgraph -lm

CC	=	gcc -l csfml-graphics -l csfml-system -l csfml-window

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C lib/my/
	make -C lib/graph/
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean