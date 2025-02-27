/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:58:46 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/27 21:02:16 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_tiles(t_game *var, int x, int y)
{
	if (var->map->map[y][x] == '0')
		mlx_put_image_to_window(var->mlx, var->win, var->bg.img,
			x * TILE, y * TILE);
	else if (var->map->map[y][x] == '1')
		mlx_put_image_to_window(var->mlx, var->win, var->wall.img,
			x * TILE, y * TILE);
	else if (var->map->map[y][x] == 'P')
		mlx_put_image_to_window(var->mlx, var->win, var->player.img,
			x * TILE, y * TILE);
	else if (var->map->map[y][x] == 'C')
		mlx_put_image_to_window(var->mlx, var->win, var->obj.img,
			x * TILE, y * TILE);
	else if (var->map->map[y][x] == 'E')
		mlx_put_image_to_window(var->mlx, var->win, var->exit.img,
			x * TILE, y * TILE);
}

void	put_map_to_window(t_game *var)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < var->map->rows)
	{
		x = 0;
		while (x < var->map->line_length)
		{
			put_tiles(var, x, y);
			x++;
		}
		y++;
	}
}

static int	move_player(t_game *var, int mv_x, int mv_y)
{
	bool	win;

	win = 0;
	if (var->map->map[var->player_y + mv_y][var->player_x + mv_x] == '1'
		|| (var->map->map[var->player_y + mv_y][var->player_x + mv_x] == 'E'
		&& var->map->obj_count > 0))
		return (0);
	else if (var->map->map[var->player_y + mv_y][var->player_x + mv_x] == 'E'
		&& var->map->obj_count == 0)
		win = 1;
	else if (var->map->map[var->player_y + mv_y][var->player_x + mv_x] == 'C')
		var->map->obj_count--;
	var->map->map[var->player_y][var->player_x] = '0';
	var->player_y += mv_y;
	var->player_x += mv_x;
	var->map->map[var->player_y][var->player_x] = 'P';
	put_map_to_window(var);
	var->m_count++;
	ft_printf("%d\n", var->m_count);
	if (win)
		close_game(var);
	return (0);
}

int	key_hook(int keycode, t_game *var)
{
	if (keycode == XK_Escape)
	{
		close_game(var);
		return (0);
	}
	else if (keycode == W_KEY)
		move_player(var, 0, -1);
	else if (keycode == S_KEY)
		move_player(var, 0, 1);
	else if (keycode == A_KEY)
		move_player(var, -1, 0);
	else if (keycode == D_KEY)
		move_player(var, 1, 0);
	return (0);
}

int	close_game(t_game *var)
{
	free_map(var->map);
	mlx_destroy_image(var->mlx, var->bg.img);
	mlx_destroy_image(var->mlx, var->wall.img);
	mlx_destroy_image(var->mlx, var->player.img);
	mlx_destroy_image(var->mlx, var->obj.img);
	mlx_destroy_image(var->mlx, var->exit.img);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	var->mlx = NULL;
	exit(0);
}
