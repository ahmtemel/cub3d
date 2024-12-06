/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:38:03 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 23:33:56 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_atoi(char *str)
{
	int				i;
	unsigned int	result;

	i = 0;
	result = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] <= 48 && str[i] >= 57)
			return (0);
		i++;
	}
	return ((int)result);
}

void	xpm_init(t_image *image)
{
	int	x;

	image->pixel_array = (int **)malloc(image->width * sizeof(int *));
	x = 0;
	while (x < image->width)
		image->pixel_array[x++] = (int *)malloc(image->height * sizeof(int));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (str == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

void	draw_wall(t_main *data, int **pixel_array)
{
	int	x;
	int	p;
	int	*length;

	x = 0;
	p = 0;
	length = length_of_collumns(data);
	which_pixel_calc(data);
	pixel_n_calc(data, length);
	p = 0;
	while (p < 60)
	{
		x = p * 32;
		upper_wall(data, length, p, x);
		lower_wall(data, length, p, x);
		p++;
	}
	free(length);
}

int	close_window(void)
{
	exit(1);
}
