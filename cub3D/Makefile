SRCS = get_next_line.c put_utils.c xpm_to_image.c main.c assault_map.c \
		get_map_utils_other.c get_map.c map_control_utils.c ray_casting.c \
		map_control_utils_two.c map_control.c ray_casting_utils.c \
		assault_map_two.c mlx_func.c mlx_func_two.c utils.c utils_two.c \
		get_map_utils.c utils_three.c split_utils.c
NAME = cub3D
MLX     =   ./mlx/libmlx.a
MLXF	=	-framework AppKit -framework OpenGL -L./mlx -lmlx -I./mlx -g
GCC_FLAG = -Wall -Wextra -Werror
GCC = gcc
OBJS	=	$(SRCS:.c=.o)
RM		=	rm -rf

all:	$(NAME)

$(NAME):	$(MLX) $(OBJS)
	$(CC) $(GCC_FLAG) $(MLXF) $(OBJS) $(MLX) -o $(NAME)

clean:
	$(RM) $(OBJS)

$(MLX):
	make -C ./mlx

fclean:
	$(RM) $(OBJS) $(NAME)
	make clean -C ./mlx

re:			fclean all

.PHONY:		all clean fclean re
