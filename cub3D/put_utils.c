/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:13:29 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 23:30:13 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	which_pixel_calc(t_main *data)
{
	int		i;
	int		j;
	int		which_block;
	float	which_collumn;
	float	exact_position;

	i = 0;
	j = 0;
	while (i < 60)
	{
		j = 0;
		if (data->ray->drc[i] == 'W' || data->ray->drc[i] == 'E')
			j = 1;
		exact_position = data->ray->ray_xy[i][j] / 64;
		which_block = (int)exact_position;
		which_collumn = exact_position - which_block;
		data->which_pixel[i] = 64 * which_collumn;
		if (data->which_pixel[i] > 64)
			data->which_pixel[i] = 64;
		else if (data->which_pixel[i] == 0)
			data->which_pixel[i] = 1;
		i++;
	}
}

int	*length_of_collumns(t_main *data)
{
	int		i;
	int		*length;
	float	*distance;

	i = 0;
	distance = ray_casting(data);
	length = malloc(sizeof(int) * 60);
	while (i < 60)
	{
		length[i] = (int)((20480 / distance[i]) * 4);
		if (length[i] > 1080)
			length[i] = 1080;
		i++;
	}
	return (length);
}

void	pixel_n_calc(t_main *data, int *length)
{
	int	i;

	i = 0;
	while (i < 60)
	{
		data->pixel_n[i] = length[i] / 64;
		i++;
	}
}

void	put_pixel(t_main *data, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * data->size_line + x * (data->bits_per_pixel / 8);
	data->data[pixel_index] = color & 0xFF;
	data->data[pixel_index + 1] = (color >> 8) & 0xFF;
	data->data[pixel_index + 2] = (color >> 16) & 0xFF;
}

int	check_path(char *str, char *drc)
{
	int	i;

	i = 0;
	if (ft_strlen(str) != ft_strlen(drc))
		return (0);
	while (str[i] || drc[i])
	{
		if (str[i] != drc[i])
			return (0);
		i++;
	}
	return (1);
}
