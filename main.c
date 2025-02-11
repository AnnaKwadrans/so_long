/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:03:51 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/10 23:08:44 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	//open - read map
	//validate map
	//

	void	*mlx;
	void	*window;
	t_data	img;
	

	mlx = mlx_init();
	if (!mlx)
		exit(1);
	window = mlx_new_window(mlx, 1000, 500, "hola");
	img.img = mlx_new_image(mlx, 1000, 500);
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
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	//mlx_key_hook(window, );
	mlx_destroy_window(mlx, window);
	
	return (0);
}
