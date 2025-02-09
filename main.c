/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:03:51 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/09 19:54:37 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
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
	window = mlx_new_window(mlx, 1000, 1500, "hola");
	img.img = mlx_new_image(mlx, 1000, 1500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght,
			&img.endian);
	my_mlx_pixel_put(&img, 1000, 1500, 0x00FF0000);
	//mlx_pixel_put(mlx, window, 1000, 1500, 0x00FF0000);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	
	return (0);
}
