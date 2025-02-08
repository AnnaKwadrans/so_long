/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:45:01 by akwadran          #+#    #+#             */
/*   Updated: 2024/12/14 15:58:30 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	len;

	if (s == NULL)
		return (ft_putstr("(null)"));
	len = 0;
	while (s[len])
	{
		write(1, &s[len], 1);
		len++;
	}
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*ptr;

	len = ft_strlen(s) + 1;
	ptr = malloc(sizeof(char) * len);
	if (ptr == NULL)
		return (ptr);
	ft_strlcpy(ptr, s, sizeof(char) * len);
	return (ptr);
}
