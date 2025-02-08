/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:54:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/08 17:03:48 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <string.h>

int	main(void)
{
	printf("%d\n", errno);
	printf("%s\n", strerror(10));
	perror("Error");

	


	return (0);
}
