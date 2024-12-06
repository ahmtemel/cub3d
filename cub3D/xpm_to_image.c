/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:59:35 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 23:31:35 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	xpm_to_int_array(t_image *image)
{
	int				bytes_per_pixel;
	unsigned char	*pixel_start;
	int				x;
	int				y;

	xpm_init(image);
	bytes_per_pixel = image->bpp / 8;
	x = 0;
	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			pixel_start = (unsigned char *)&image->data[y * image->sizeline + x
				* bytes_per_pixel];
			image->a = pixel_start[3];
			image->r = pixel_start[2];
			image->g = pixel_start[1];
			image->b = pixel_start[0];
			image->pixel_array[x++][y] = (image->a << 24) | \
			(image->r << 16) | (image->g << 8) | image->b;
		}
		y++;
	}
}

void	check_same_texture(t_main *main)
{
	if (check_path(main->no, main->so) || check_path(main->no, main->we)
		|| check_path(main->no, main->ea))
		exit(1);
	if (check_path(main->so, main->we) || check_path(main->no, main->ea))
		exit(1);
	if (check_path(main->we, main->ea))
		exit(1);
}

void	is_image_exists(t_main *main)
{
	if (open(main->so, O_RDONLY) == -1)
		exit(1);
	if (open(main->no, O_RDONLY) == -1)
		exit(1);
	if (open(main->we, O_RDONLY) == -1)
		exit(1);
	if (open(main->ea, O_RDONLY) == -1)
		exit(1);
	check_same_texture(main);
}

void	image_creater(t_main *data)
{
	is_image_exists(data);
	data->image_w->image = mlx_xpm_file_to_image(data->mlx_ptr, \
		(char *)data->no, &data->image_w->width, &data->image_w->height);
	data->image_e->image = mlx_xpm_file_to_image(data->mlx_ptr, \
		(char *)data->so, &data->image_e->width, &data->image_e->height);
	data->image_n->image = mlx_xpm_file_to_image(data->mlx_ptr, \
		(char *)data->ea, &data->image_n->width, &data->image_n->height);
	data->image_s->image = mlx_xpm_file_to_image(data->mlx_ptr, \
		(char *)data->we, &data->image_s->width, &data->image_s->height);
	data->image_w->data = mlx_get_data_addr(data->image_w->image, \
		&data->image_w->bpp, &data->image_w->sizeline, &data->image_w->endian);
	data->image_e->data = mlx_get_data_addr(data->image_e->image, \
		&data->image_e->bpp, &data->image_e->sizeline, &data->image_e->endian);
	data->image_s->data = mlx_get_data_addr(data->image_s->image, \
		&data->image_s->bpp, &data->image_s->sizeline, &data->image_s->endian);
	data->image_n->data = mlx_get_data_addr(data->image_n->image, \
		&data->image_n->bpp, &data->image_n->sizeline, &data->image_n->endian);
	xpm_to_int_array(data->image_w);
	xpm_to_int_array(data->image_e);
	xpm_to_int_array(data->image_s);
	xpm_to_int_array(data->image_n);
}

void	image_putter(t_main *data)
{
	draw_background(data);
	draw_wall(data, data->image_w->pixel_array);
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_key_press, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
