CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = cube3D

SRCS_GNL = ./get_next_line/get_next_line_utils.c ./get_next_line/get_next_line.c

SRCS = main.c raycast.c render.c ray.c color.c input.c parsing.c

OBJS_GNL := $(SRCS_GNL:.c=.o)

OBJS := $(SRCS:.c=.o)

LIBFT = make -C ./libft

all: $(NAME)

$(NAME) : $(OBJS) $(OBJS_GNL) DO_LIBFT
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(OBJS_GNL) minilibx/libmlx.a libft/libft.a -L/usr/X11R6/lib -lX11 -lXext -lm 
	@echo "🥚🦖Compilation👻completed🥚🦖"

DO_LIBFT:
	$(LIBFT)

clean :
	rm -f $(OBJS)
	$(LIBFT) clean


fclean : clean
	rm -f $(NAME)
	$(LIBFT) fclean


re : fclean all

# dolibft :
# 	@make -C ./libft all > /dev/null


debug :
	$(CC) -g -o $(NAME)debug $(SRCS) minilibx/libmlx_Linux.a -lX11 -lXext -lm