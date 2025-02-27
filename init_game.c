/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:32:47 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/27 21:07:22 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	break_init(t_game *var)
{
	free_map(var->map);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	var->mlx = NULL;
}

void	init_game(t_game *var, char *file)
{
	size_t	x;
	size_t	y;

	var->mlx = mlx_init();
	if (!var->mlx)
		return (ft_printf("Error\nFailed mlx init\n"), exit(1));
	var->map = init_map(file);
	if (!var->map)
		return (ft_printf("Error\nFailed map init\n"), exit(1));
	if (!validate_map(var->map, var))
	{
		break_init(var);
		return (ft_printf("Error\nMap not valid\n"), exit(1));
	}
	x = var->map->line_length * TILE;
	y = var->map->rows * TILE;
	var->win = mlx_new_window(var->mlx, x, y, "so_long");
	if (!var->win)
	{
		break_init(var);
		return (ft_printf("Error\nFailed window init\n"), exit(1));
	}
	init_imgs(var);
	var->m_count = 0;
	put_map_to_window(var);
}

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

t_map	*init_map(char *file)
{
	int		fd;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (ft_printf("Error\nFailed to open file\n"), NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_printf("Error\nFailed malloc\n"), NULL);
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
	var->wall.addr = mlx_get_data_addr(&var->wall.img,
			&var->wall.bits_per_pixel, &var->wall.line_length,
			&var->wall.endian);
	var->player.img = mlx_xpm_file_to_image(var->mlx, "textures/player.xpm",
			&var->player.line_length, &var->player.bits_per_pixel);
	var->player.addr = mlx_get_data_addr(&var->player.img,
			&var->player.bits_per_pixel, &var->player.line_length,
			&var->player.endian);
	var->obj.img = mlx_xpm_file_to_image(var->mlx, "textures/obj.xpm",
			&var->obj.line_length, &var->obj.bits_per_pixel);
	var->obj.addr = mlx_get_data_addr(&var->obj.img,
			&var->obj.bits_per_pixel, &var->obj.line_length,
			&var->obj.endian);
	var->exit.img = mlx_xpm_file_to_image(var->mlx, "textures/exit.xpm",
			&var->exit.line_length, &var->exit.bits_per_pixel);
	var->exit.addr = mlx_get_data_addr(&var->exit.img,
			&var->exit.bits_per_pixel, &var->exit.line_length,
			&var->exit.endian);
}
