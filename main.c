/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:03:51 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/12 20:54:03 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_vars *var, t_data *img)
	{
		if (keycode == XK_Escape)
		{
			mlx_destroy_window((var)->mlx, (var)->win);
			mlx_destroy_display((var)->mlx);
			mlx_destroy_image((var)->mlx, (img)->img);
			free ((var)->mlx);
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



//int	main(int argc, char **argv)
int	main(void)
{
	//open - read map
	//validate map
	//

	//void	*mlx;
	//void	*window;
	t_vars	var;
	t_data	img;
	

	var.mlx = mlx_init();
	if (!var.mlx)
		exit(1);
	var.win = mlx_new_window(var.mlx, 1000, 500, "hola");
	img.img = mlx_new_image(var.mlx, 1000, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	
	
	int	i;
	int	j;
	i = 0;



	while (i++ < 400)
	{
		j = 0;
		while (j++ < 200)
		{
			my_mlx_pixel_put(&img, 15 + i, 15 + j, 0x00FF0000);
		}
	}
	
	//*(unsigned int *)(img.addr + (100 * img.line_length + 150) * (img.bits_per_pixel / 8)) = 0x00FF0000;
	//mlx_pixel_put(mlx, window, 1000, 500, 0x00FF0000);
	mlx_put_image_to_window(var.mlx, var.win, img.img, 0, 0);
	mlx_key_hook(var.win, key_hook, &var);
	mlx_loop(var.mlx);
	//mlx_key_hook(window, );
	
	
	return (0);
}
