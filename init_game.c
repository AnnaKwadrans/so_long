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
	int	x;
	int	y;

	var->mlx = mlx_init();
	if (!var->mlx)
		return (perror("Err: Failed mlx init"), exit(1));
	var->map = init_map(file);
	if (!var->map)
		return (perror("Err: Failed map init"), exit(1));
	if (!validate_map(var->map, var))
		return (perror("Error\nNot valid map"), exit(1));
	var->win = mlx_new_window(var->mlx, var->map->line_length * TILE,
		var->map->rows * TILE, "so_long");
	
	x = var->map->line_length * TILE;
	y = var->map->rows * TILE;

	var->bg.img = mlx_new_image(var->mlx, x, y);
	var->bg.addr = mlx_get_data_addr(&var->bg.img, &var->bg.bits_per_pixel, &var->bg.line_length,
			&var->bg.endian);
	var->bg.img = mlx_xpm_file_to_image(var->mlx, "textures/grass.xpm", &var->bg.line_length, &var->bg.bits_per_pixel);
	

	//init_img(var, &var->bg, "textures/grass.xpm", x, y);
	//init_img(var, &var->wall, "textures/wall.xpm", x, y);
	//init_img(var, &var->player, "textures/player.xpm", x, y);
	
	//init_img(var, &var->chest, "textures/chest.xpm", x, y);
	//init_img(var, &var->exit, "textures/exit.xpm", x, y);
}
/*
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
*/
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
	printf("%ld\n", map->rows);
	close(fd);
	if (map->rows == 0)
		return (NULL);
	map->map = get_map_array(file, &map->line_length, map->rows);
	if (!map->map)
		return (NULL);
	return (map);	
}

void	init_img(t_game *var, t_data *img, char *file, int x, int y)
{
	img = mlx_new_image(var->mlx, x, y);
	img->addr = mlx_get_data_addr(&img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->img = mlx_xpm_file_to_image(var->mlx, file, &img->line_length, &img->bits_per_pixel);
	
	
	/*
	var->wall.img = mlx_new_image(var->mlx, var->map->line_length * TILE, var->map->rows * TILE);
	var->wall.addr = mlx_get_data_addr(&var->wall.img, &var->wall.bits_per_pixel, &var->wall.line_length, &var->wall.endian);
	var->wall.img = mlx_xpm_file_to_image(var->mlx, "textures/wall.xpm", &var->wall.line_length, &var->wall.bits_per_pixel);
	var->player.img = mlx_new_image(var->mlx, var->map->line_length * TILE, var->map->rows * TILE);
	var->player.addr = mlx_get_data_addr(&var->player.img, &var->player.bits_per_pixel, &var->player.line_length,
			&var->player.endian);
	var.player.img = mlx_xpm_file_to_image(var.mlx, "textures/player.xpm", &var.player.line_length, &var.player.bits_per_pixel);
	var->bg.img = mlx_new_image(var->mlx, var->map->line_length * TILE, var->map->rows * TILE);
	var->bg.addr = mlx_get_data_addr(&var->bg.img, &var->bg.bits_per_pixel, &var->bg.line_length,
			&var->bg.endian);
	var->chest.img = mlx_xpm_file_to_image(var->mlx, "textures/chest.xpm", &var->chest.line_length, &chest->bg.bits_per_pixel);
	var->bg.img = mlx_new_image(var->mlx, var->map->line_length * TILE, var->map->rows * TILE);
	var->bg.addr = mlx_get_data_addr(&var->bg.img, &var->bg.bits_per_pixel, &var->bg.line_length,
			&var->bg.endian);
	var->bg.img = mlx_xpm_file_to_image(var->mlx, "textures/grass.xpm", &var->bg.line_length, &var->bg.bits_per_pixel);
	*/
}
