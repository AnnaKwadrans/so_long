/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:26:22 by akwadran          #+#    #+#             */
/*   Updated: 2025/01/06 12:57:24 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_strlen(char c, char const *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static int	split_count(char const *s, char c)
{
	int	count;
	int	new_string;

	new_string = 0;
	count = 0;
	while (*s != '\0')
	{
		if (*s == c)
			new_string = 0;
		else if (*s != c && new_string == 0)
		{
			new_string = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**init_array(char const *s, int count, char c)
{
	char	**array;
	int		i;

	array = (char **)ft_calloc(count + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s != '\0' && *s == c)
			s++;
		array[i] = (char *)ft_calloc(split_strlen(c, s) + 1, sizeof(char));
		if (array[i] == NULL)
		{
			free_array(array);
			return (NULL);
		}
		while (*s != '\0' && *s != c)
			s++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**array;
	int		i;

	count = split_count(s, c);
	array = init_array(s, count, c);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		while (*s != '\0' && *s == c)
			s++;
		ft_strlcpy(array[i], s, split_strlen(c, s) + 1);
		while (*s != '\0' && *s != c)
			s++;
		i++;
	}
	return (array);
}
