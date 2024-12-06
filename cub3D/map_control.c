/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:11:20 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 21:11:24 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*result;

	result = (char *)haystack;
	if (!*needle)
		return (result);
	i = 0;
	while (i < len && *(result + i))
	{
		j = 0;
		while (*(result + i + j) == *(needle + j) && i + j < len)
		{
			if (*(needle + j + 1) == '\0')
				return (result + i);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
		return (1);
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;

	c = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&str[i]);
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		till_i_collapse;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	till_i_collapse = ft_strlen(s1) - 1;
	while (till_i_collapse && ft_strchr(set, s1[till_i_collapse]))
		till_i_collapse--;
	result = ft_substr(s1, 0, till_i_collapse + 1);
	if (result == NULL)
		return (0);
	return (result);
}

void	wrong_argument_exit(t_main *main, int error_code)
{
	(void)main;
	if (error_code == 10)
		printf("Wrong Argument Error\n");
	else if (error_code == 11)
		printf("The Map Name is Invalid Error\n");
	exit(error_code);
}
