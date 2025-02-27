RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
NAME = so_long
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
MLX_DIR = mlx
MLX = $(MLX_DIR)libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lbsd

SRC = main.c init_game.c validate_map.c run_game.c map_utils.c

OBJ = $(SRC:.c=.o)

%.o:	%.c so_long.h
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I/opt/X11/include -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) -I$(MLX_DIR) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

.PHONY: all clean fclean re

all:	$(NAME)

clean:	
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME) $(LIBFT)
	make clean -C $(MLX_DIR)

re:	fclean all
