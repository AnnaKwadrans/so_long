/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:03:51 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/22 18:19:00 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
*/





int	main(int argc, char **argv)
//int	main(void)
{
	//open - read map
	//validate map
	//
	//if (argc != 2)
	//	exit (1);
	//handle_map(argv[1]);
	//void	*mlx;
	//void	*window;
	t_game	var;
	//t_data	img;
	
	if (argc >= 2)
		init_game(&var, argv[1]);
	else
		return (ft_putendl_fd("Err: No argument", 1), 0);
	/*
	var.mlx = mlx_init();
	if (!var.mlx)
		exit(1);
	if (!(argc == 2))
		exit(1);
	var.map = handle_map(argv[1]);
	
	find_player(&var);
	*/
	/*
	var.win = mlx_new_window(var.mlx, var.map->line_length * TILE, var.map->rows * TILE, "hola");
	var.bg.img = mlx_new_image(var.mlx, var.map->line_length * TILE, var.map->rows * TILE);
	var.bg.addr = mlx_get_data_addr(&var.bg.img, &var.bg.bits_per_pixel, &var.bg.line_length,
			&var.bg.endian);
	var.bg.img = mlx_xpm_file_to_image(var.mlx, "textures/grass.xpm", &var.bg.line_length, &var.bg.bits_per_pixel);
	var.wall.img = mlx_xpm_file_to_image(var.mlx, "textures/wall.xpm", &var.wall.line_length, &var.wall.bits_per_pixel);
	var.player.img = mlx_xpm_file_to_image(var.mlx, "textures/player.xpm", &var.player.line_length, &var.player.bits_per_pixel);
	*/
	//var.img = &img;
	/*
	int	i;
	int	j;
	i = 0;



	while (i++ < 16)
	{
		j = 0;
		while (j++ < 16)
		{
			my_mlx_pixel_put(var.img->img, 15 + i, 15 + j, 0x00FF0000);
		}
	}
	*/
	//*(unsigned int *)(img.addr + (100 * img.line_length + 150) * (img.bits_per_pixel / 8)) = 0x00FF0000;
	//mlx_pixel_put(mlx, window, 1000, 500, 0x00FF0000);
	//mlx_put_image_to_window(var.mlx, var.win, var.img[0].img, 0, 0);
	
	
	
	put_map_to_window(&var);
	
	
	mlx_key_hook(var.win, key_hook, &var);
	mlx_hook(var.win, 17, 0, close_game, &var);
	mlx_loop(var.mlx);
	//mlx_destroy_image(var.mlx, var.img->img);
	//mlx_destroy_window(var.mlx, var.win);
	//mlx_destroy_display(var.mlx);
	//free(var.mlx);
	
	
	//mlx_key_hook(window, );
	
	
	return (0);
}
