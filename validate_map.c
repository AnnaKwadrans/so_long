/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:02:38 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/13 22:05:04 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	get_rows(int fd)
{
	size_t	rows;
	char	*buffer;

	buffer = malloc(sizeof(char));
	if (!buffer)
		return (0);
	rows = 1;
	while (read(fd, buffer, 1))
	{
		if (*buffer == '\n')
			rows++;
	}
	close(fd);
	return (rows);
}

t_map	*init_map(int fd, char *file)
{
	t_map	*map;
	int	i;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->rows = get_rows(fd);
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	fd = open(file, O_RDONLY);
	i = 0;
	map->map[i] = get_next_line(fd);
	map->line_length = ft_strlen(map->map[i]) - 1;
	map->map[i][map->line_length] = '\0';
	while (map->map[i])
	{
		i++;
		map->map[i] = get_next_line(fd);
		if (map->map[i])
			map->map[i][map->line_length] = '\0';
	}
	map->map[i] = NULL;
	return (map);
}

bool	is_rectangular(t_map map)
{
	int	i;

	i = 0;
	while (map.map[i])
	{
		if (ft_strlen(map.map[i]) != map.line_length)
			return (0);
		i++;
	}
	return (1);
}

bool	has_wall(t_map map)
{
	size_t	i;

	i = 0;
	while (map.map[0][i] && map.map[map.line_length - 1])
	{
		if (map.map[0][i] != '1' || *(map).map[map.line_length - 1] != '1')
			return (0);
		i++;
	}
	i = 1;
	while (i < map.line_length - 2)
	{
		if (map.map[i][0] != '1' || map.map[i][map.line_length - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

t_map	*handle_map(char *file)
{
	int		fd;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		exit(1);
	map = init_map(fd, file);
	//validate
	return (map);
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



