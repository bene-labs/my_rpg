##
## EPITECH PROJECT, 2019
## Makefile my_rpg
## File description:
## makes my_rpg
##

SRC	=	src/main.c					\
		src/draw_sprites.c				\
		src/load_rooms.c				\
		src/create_initial_objects.c			\
		src/str_functions.c				\
		src/score.c					\
		src/player.c					\
		src/projectile.c				\
		src/my_printf/disp_stdarg.c			\
		src/my_printf/disp_stdarg2.c			\
		src/my_printf/disp_stdarg3.c			\
		src/my_printf/disp_stdarg4.c			\
		src/my_printf/my_putstr.c			\
		src/my_printf/my_putchar.c			\
		src/my_printf/my_put_nbr.c			\
		src/my_printf/my_put_nbr_base.c			\
		src/my_printf/my_printf.c			\
		src/my_printf/my_strlen.c			\
		src/my_printf/my_getnbr.c			\
		src/map_generation.c				\
		src/enemies.c					\
		src/list_help_functions.c			\
		src/healthbar.c					\
		src/colision.c					\
		src/npc.c					\
		src/buttons.c					\
		src/boss.c					\
		src/handle_randomness.c

OBJ	=	$(SRC:.c=.o)

RM	=	rm -rf

NAME	=	my_rpg

#CFLAGS	+=    -W -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -l csfml-window -l csfml-graphics -l csfml-system -l csfml-audio -lm

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all  clean fclean re
