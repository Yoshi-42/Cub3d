CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = Cub3D

SRCS = main.c raycast.c render.c ray.c color.c input.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) minilibx/libmlx.a -L/usr/X11R6/lib -lX11 -lXext -lm 
	@echo "🥚🦖Compilation completed🥚🦖"

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

dolibft :
	@make -C ./libft all > /dev/null

debug :
	$(CC) -g -o $(NAME)debug $(SRCS) minilibx/libmlx_Linux.a -lX11 -lXext -lm