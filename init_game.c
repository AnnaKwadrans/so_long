/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:32:47 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/22 18:18:43 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *var, char *file)
{	
	size_t	x;
	size_t	y;
	
	var->mlx = mlx_init();
	if (!var->mlx)
		return (perror("Err: Failed mlx init"), exit(1));
	var->map = init_map(file);
	if (!var->map)
		return (perror("Err: Failed map init"), exit(1));
	if (!validate_map(var->map, var))
		return (perror("Error\nNot valid map"), exit(1));
	x = var->map->line_length * TILE;
	y = var->map->rows * TILE;
	var->win = mlx_new_window(var->mlx, x, y, "so_long");
	if (!var->win)
	{
		free_map(var->map);
		mlx_destroy_display(var->mlx);
		free(var->mlx);
		var->mlx = NULL;
		return (perror("Err: Failed window init"), exit(1));
	}
	init_imgs(var);
	var->m_count = 0;
	put_map_to_window(var);
}

/*
static size_t	get_rows(int fd)
{
	size_t	rows;
	char	*buffer;
	int	b_read;

	buffer = malloc(sizeof(char));
	if (!buffer)
		return (perror("Err: Failed malloc"), 0);
	rows = 1;
	b_read = 1;
	while (b_read != 0)
	{
		b_read = read(fd, buffer, 1);
		printf("%c\n", buffer[0]);
		if (b_read < 0)
			return (perror("Err: Failed to read file"), 0);
		if (*buffer == '\n')
			rows++;
		b_read = read(fd, buffer, 1);
		//printf("%ld\n", rows);
	}
	return (rows);
}
*/

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
	free(buffer);
	buffer = NULL;
	return (rows);
}

static char	**get_map_array(char *file, size_t *line_length, size_t rows)
{
	int	fd;
	int	i;
	char	**map_array;

	map_array = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!map_array)
		return (perror("Err: Failed malloc"), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Err: Failed to open file"), NULL);
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

t_map	*init_map(char *file)
{
	int	fd;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (perror("Err: Failed to open file"), NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (perror("Err: Failed malloc"), NULL);
	map->rows = get_rows(fd);
	close(fd);
	if (map->rows == 0)
		return (NULL);
	map->map = get_map_array(file, &map->line_length, map->rows);
	if (!map->map)
		return (NULL);
	return (map);	
}

void	init_imgs(t_game *var)
{
	var->bg.img = mlx_xpm_file_to_image(var->mlx, "textures/bg.xpm",
		&var->bg.line_length, &var->bg.bits_per_pixel);
	var->bg.addr = mlx_get_data_addr(&var->bg.img, &var->bg.bits_per_pixel,
		&var->bg.line_length, &var->bg.endian);
	var->wall.img = mlx_xpm_file_to_image(var->mlx, "textures/wall.xpm",
		&var->wall.line_length, &var->wall.bits_per_pixel);
	var->wall.addr = mlx_get_data_addr(&var->wall.img, &var->wall.bits_per_pixel,
		&var->wall.line_length, &var->wall.endian);
	var->player.img = mlx_xpm_file_to_image(var->mlx, "textures/player.xpm",
		&var->player.line_length, &var->player.bits_per_pixel);
	var->player.addr = mlx_get_data_addr(&var->player.img,
		&var->player.bits_per_pixel, &var->player.line_length,
		&var->player.endian);
	var->chest.img = mlx_xpm_file_to_image(var->mlx, "textures/chest.xpm",
		&var->chest.line_length, &var->chest.bits_per_pixel);
	var->chest.addr = mlx_get_data_addr(&var->chest.img,
		&var->chest.bits_per_pixel, &var->chest.line_length, &var->chest.endian);
	var->exit.img = mlx_xpm_file_to_image(var->mlx, "textures/exit.xpm",
		&var->exit.line_length, &var->exit.bits_per_pixel);
	var->exit.addr = mlx_get_data_addr(&var->exit.img, &var->exit.bits_per_pixel, &var->exit.line_length,
		&var->exit.endian);
}
