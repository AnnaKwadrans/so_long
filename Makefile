RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = so_long
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
MLX_DIR = mlx/
MLX = $(MLX_DIR)mlx.a

SRC = main.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ)  -Lmlx_linux -lmlx_Linux -L$(LIBFT_DIR) -lft -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

.PHONY: all clean fclean re

all:	$(NAME)

clean:	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean:	clean
	$(RM) $(NAME) $(LIBFT)
	make clean -C $(MLX_DIR)

re:	clean all
