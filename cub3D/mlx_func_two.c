/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:21:25 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 21:53:40 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_background(t_main *main)
{
	int	x;
	int	y;
	int	color;

	x = -1;
	y = 0;
	while (++x <= 1920)
	{
		y = 0;
		while (y <= 540)
			put_pixel(main, x, y++, main->color_c);
	}
	x = -1;
	while (++x < 1920)
	{
		y = 540;
		while (y < 1080)
			put_pixel(main, x, y++, main->color_f);
	}
}

void	repeater(t_main *data, int x, int y, int color)
{
	int	x_backup;
	int	n;

	x_backup = x + 32;
	while (x < x_backup)
	{
		put_pixel(data, x, y, color);
		x++;
	}
}

void	compass(t_main *data, int p, int buffer, int x)
{
	if (data->ray->drc[p] == 'W')
		repeater(data, x, buffer,
			data->image_w->pixel_array[data->which_pixel[p]][data->i]);
	else if (data->ray->drc[p] == 'E')
		repeater(data, x, buffer,
			data->image_e->pixel_array[data->which_pixel[p]][data->i]);
	else if (data->ray->drc[p] == 'N')
		repeater(data, x, buffer,
			data->image_n->pixel_array[data->which_pixel[p]][data->i]);
	else
		repeater(data, x, buffer,
			data->image_s->pixel_array[data->which_pixel[p]][data->i]);
}

void	upper_wall(t_main *data, int *length, int p, int x)
{
	int	n;
	int	y;
	int	buffer;
	int	buffer_y;

	y = 540;
	data->i = 32;
	buffer_y = 540 - (length[p] / 2);
	while (y > buffer_y)
	{
		n = 0;
		while (n < data->pixel_n[p])
		{
			buffer = y;
			if (buffer >= 1080)
				buffer = 1079;
			if (buffer >= 0)
				compass(data, p, buffer, x);
			y--;
			n++;
		}
		data->i--;
		if (data->i <= 0)
			data->i = 0;
	}
}

void	lower_wall(t_main *data, int *length, int p, int x)
{
	int	n;
	int	y;
	int	buffer;

	y = 0;
	data->i = 32;
	while (y < (length[p] / 2))
	{
		n = 0;
		while (n < data->pixel_n[p] + 1)
		{
			buffer = y + 540;
			if (buffer >= 1080)
				buffer = 1079;
			if (buffer >= 0)
				compass(data, p, buffer, x);
			y++;
			n++;
		}
		data->i++;
		if (data->i >= 64)
			data->i = 63;
	}
}
