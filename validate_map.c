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

// .ber
// 1 exit, >0 obj, 1 player
// camino valido

// Error\nMensaje explícito

static bool	find_player(t_game *var)
{
	size_t	x;
	size_t	y;

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
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
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

	//printf("%ld, %ld\n", map->line_length, map->rows);
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

/*
static bool	valid_route(t_map *map)
{
	
}
*/
bool	validate_map(t_map *map, t_game *var)
{
	if (has_wall(map) && is_rectangular(map) && find_player(var)
		&& find_objs(var))
		return (1);
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


