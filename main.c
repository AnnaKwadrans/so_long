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

static bool	is_ber (char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 4] == '.' && file[len - 3] == 'b' && file[len - 2] == 'e'
		&& file[len - 1] == 'r')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	var;

	if (argc >= 2 && is_ber(argv[1]))
		init_game(&var, argv[1]);
	else
		return (ft_putendl_fd("Error\nNo valid argument", 1), 0);
	mlx_key_hook(var.win, key_hook, &var);
	mlx_hook(var.win, NOTIFY_DESTROY, 0, close_game, &var);
	mlx_loop(var.mlx);
	return (0);
}
