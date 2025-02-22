/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:54:10 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/22 17:47:30 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/keysym.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# define TILE 16

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

typedef struct s_map
{
	char	**map;
	size_t	line_length;
	size_t	rows;
}		t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_data	bg;
	t_data	wall;
	t_data	player;
	t_data	chest;
	t_data	exit;
	int		player_x;
	int		player_y;
}		t_game;

void	init_game(t_game *var, char *file);
t_map	*init_map(char *file);
bool	validate_map(t_map *map, t_game *var);
void	init_img(t_game *var, t_data *img, char *file, int x, int y);

void	free_map(t_map *map);

//t_map	*handle_map(char *file);
void	print_map(t_map *map);
void    put_map_to_window(t_game *var);
//void    print_walls(t_game var);
//void    find_player(t_game *var);

#endif
