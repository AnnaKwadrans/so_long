/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:02:38 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/27 21:30:23 by akwadran         ###   ########.fr       */
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

static bool	valid_route(char **map, int obj_count, int y, int x)
{
	static bool	exit = 0;
	static int	objs = 0;

	if (map[y][x] == 'E')
		exit = 1;
	if (map[y][x] == 'C')
		objs++;
	if (exit && objs == obj_count)
		return (1);
	if (map[y][x] != '1' && map[y][x] != 'x')
	{
		map[y][x] = 'x';
		return (valid_route(map, obj_count, y, x + 1)
			|| valid_route(map, obj_count, y, x - 1)
			|| valid_route(map, obj_count, y + 1, x)
			|| valid_route(map, obj_count, y - 1, x));
	}
	return (0);
}

bool	validate_map(t_map *map, t_game *var)
{
	t_map	*dup;
	bool	route_ok;

	if (has_wall(map) && is_rectangular(map) && count_elem(var, 'P') == 1
		&& count_elem(var, 'E') == 1 && count_elem(var, 'C') > 0)
	{
		var->map->obj_count = count_elem(var, 'C');
		dup = dup_map(map);
		route_ok = valid_route(dup->map, var->map->obj_count, var->player_y,
				var->player_x);
		free_map(dup);
		return (route_ok);
	}
	return (0);
}
