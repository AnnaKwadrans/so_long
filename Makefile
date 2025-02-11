RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
NAME = so_long
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
MLX_DIR = mlx/
MLX = $(MLX_DIR)libmlx.a
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRC = main.c

OBJ = $(SRC:.c=.o)

%.o:	%.c so_long.h
	$(CC) $(CFLAGS) -I$(MLX_DIR) -Imlx -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) -I$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)

.PHONY: all clean fclean re

all:	$(NAME)

clean:	
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME) $(LIBFT)


re:	fclean all
