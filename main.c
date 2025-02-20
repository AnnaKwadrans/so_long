/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:03:51 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/13 21:43:10 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_game(t_game *var)
{
	mlx_destroy_image((var)->mlx, (var)->img->img);
	mlx_destroy_window((var)->mlx, (var)->win);
	mlx_destroy_display((var)->mlx);
	free((var)->map);
	var->map = NULL;
	free((var)->mlx);
	var->mlx = NULL;
	return (0);
}

int	key_hook(int keycode, t_game *var)
	{
		if (keycode == XK_Escape)
		{
			mlx_destroy_image((var)->mlx, (var)->img->img);
			mlx_destroy_window((var)->mlx, (var)->win);
			mlx_destroy_display((var)->mlx);
			
			//free((img)->img);
			free((var)->mlx);
			return (0);
		}
		else if (keycode == XK_W)
		{

		}
		else if (keycode == XK_S)
		{

		}
		else if (keycode == XK_A)
		{

		}
		else if (keycode == XK_D)
		{

		}
		printf("KEY");
		return (0);
	}



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
	

	var.mlx = mlx_init();
	if (!var.mlx)
		exit(1);
	if (!(argc == 2))
		exit(1);
	var.map = handle_map(argv[1]);
	print_map(var.map);
	var.win = mlx_new_window(var.mlx, var.map->line_length * TILE, var.map->rows * TILE, "hola");
	var.img[0].img = mlx_new_image(var.mlx, var.map->line_length * TILE, var.map->rows * TILE);
	var.img[0].addr = mlx_get_data_addr(&var.img[0].img, &var.img[0].bits_per_pixel, &var.img[0].line_length,
			&var.img[0].endian);
	var.img[0].img = mlx_xpm_file_to_image(var.mlx, "textures/grass.xpm", &var.img[0].line_length, &var.img[0].bits_per_pixel);
	
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
	mlx_put_image_to_window(var.mlx, var.win, var.img[0].img, 0, 0);
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
