/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:02:38 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/22 17:57:52 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_elem(t_game *var, char c)
{
	size_t	x;
	size_t	y;
	int		count;

	count = 0;
	y = 0;
	while (y < var->map->rows)
	{
		x = 0;
		while (x < var->map->line_length)
		{
			if (var->map->map[y][x] == c)
			{
				count++;
				if (c == 'P')
				{
					var->player_y = y;
					var->player_x = x;
				}
			}
			x++;
		}
		y++;
	}
	return (count);
}

static bool	is_rectangular(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (ft_strlen(map->map[i]) != map->line_length)
			return (0);
		i++;
	}
	return (1);
}

// .ber
// 1 exit, >0 obj, 1 player
// camino valido

// Error\nMensaje explícito
/*
static bool	find_player(t_game *var)
{
	size_t	x;
	size_t	y;
	int		player_count;

	player count = 0;
	y = 0;
	while (y < var->map->rows)
	{
		x = 0;
		while (x < var->map->line_length)
		{
			if (var->map->map[y][x] == 'P')
			{
				var->player_y = y;
				var->player_x = x;
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count == 1)
		return (1);
	return (0);
}
*/
/*
static bool	is_rectangular(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (ft_strlen(map->map[i]) != map->line_length)
			return (0);
		i++;
	}
	return (1);
}
*/
static bool	has_wall(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->line_length)
	{
		if (map->map[0][i] != '1' || map->map[map->rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 1;
	while (i < map->rows - 1)
	{
		if (map->map[i][0] != '1' || map->map[i][map->line_length - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}
/*
static bool	find_objs(t_game *var)
{
	size_t	x;
	size_t	y;

	var->map->obj_count = 0;
	y = 0;
	while (y < var->map->rows)
	{
		x = 0;
		while (x < var->map->line_length)
		{
			if (var->map->map[y][x] == 'C')
				var->map->obj_count++;
			x++;
		}
		y++;
	}
	if (var->map->obj_count > 0)
		return (1);
	return (0);
}
*/

static bool	valid_route(char **map, int obj_count, int y, int x)
{
	static bool	exit = 0;
	static int obj = 0;

	ft_printf("x: %d y: %d c: %c\n", x, y, map[y][x]);
	if (map[y][x] == 'E')
		exit = 1;
	if (map[y][x] == 'C')
		obj++;
	if (exit && obj == obj_count)
		return (1);
	if (map[y][x] != '1')
	{
		return (valid_route(map, obj_count, y, x + 1) ||
		valid_route(map, obj_count, y, x - 1) ||
		valid_route(map, obj_count, y + 1, x) ||
		valid_route(map, obj_count, y - 1, x));
	}
}

bool	validate_map(t_map *map, t_game *var)
{	
	if (has_wall(map) && is_rectangular(map) && count_elem(var, 'P') == 1
		&& count_elem(var, 'E') == 1 && count_elem(var, 'C') > 0)
	{
		var->map->obj_count = count_elem(var, 'C');
		return (valid_route(map->map, var->map->obj_count, var->player_y,
			var->player_x));
	}
	return (0);
}

void	print_map(t_map *map)
{
	//size_t	x;
	size_t	y;

	y = 0;
	//while (y < map->rows)
	while (map->map[y])
	{
		/*x = 0;
		while (x < map->line_length)
		{
			printf("%c", map->map[x][y]);
			x++;
		}
		printf("\n");*/
		ft_putendl_fd(map->map[y], 1);
		free(map->map[y]);
		y++;
	}
	free(map->map);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	map->map = NULL;
	free(map);
	map = NULL;
}


