/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:54:10 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/27 21:07:24 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/keysym.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# define TILE 32
# define NOTIFY_DESTROY 17
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_map
{
	char	**map;
	size_t	line_length;
	size_t	rows;
	int		obj_count;
}		t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_data	bg;
	t_data	wall;
	t_data	player;
	t_data	obj;
	t_data	exit;
	int		player_x;
	int		player_y;
	int		m_count;
}		t_game;

void	init_game(t_game *var, char *file);
t_map	*init_map(char *file);
bool	validate_map(t_map *map, t_game *var);
void	init_imgs(t_game *var);

void	put_map_to_window(t_game *var);
int		key_hook(int keycode, t_game *var);
int		close_game(t_game *var);

char	**get_map_array(char *file, size_t *line_length, size_t rows);
void	free_map(t_map *map);
t_map	*dup_map(t_map *map);

void	print_map(t_map *map);

#endif
