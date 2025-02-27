/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:53:33 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/27 21:05:17 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**get_map_array(char *file, size_t *line_length, size_t rows)
{
	int		fd;
	int		i;
	char	**map_array;

	map_array = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!map_array)
		return (ft_printf("Error\nFailed malloc\n"), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nFailed to open file\n"), NULL);
	i = 0;
	map_array[i] = get_next_line(fd);
	*line_length = ft_strlen(map_array[i]) - 1;
	map_array[i][*line_length] = '\0';
	while (map_array[i])
	{
		i++;
		map_array[i] = get_next_line(fd);
		if (map_array[i])
			map_array[i][*line_length] = '\0';
	}
	map_array[i] = NULL;
	close(fd);
	return (map_array);
}

t_map	*dup_map(t_map *map)
{
	t_map	*dup;
	int		i;

	dup = malloc(sizeof(t_map));
	dup->map = (char **)malloc(sizeof(char *) * (map->rows + 1));
	i = 0;
	while (map->map[i])
	{
		dup->map[i] = ft_strdup(map->map[i]);
		i++;
	}
	dup->map[i] = NULL;
	return (dup);
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
