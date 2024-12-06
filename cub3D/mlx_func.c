/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:30:57 by ahmtemel          #+#    #+#             */
/*   Updated: 2024/03/06 23:50:28 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_key_press_dgr(int keycode, t_main *main)
{
	if (keycode == 124)
	{
		main->ray->pa -= 5;
		main->ray->pdx = cos(deg_to_rad(main->ray->pa));
		main->ray->pdy = -sin(deg_to_rad(main->ray->pa));
	}
	if (keycode == 123)
	{
		main->ray->pa += 5;
		main->ray->pdx = cos(deg_to_rad(main->ray->pa));
		main->ray->pdy = -sin(deg_to_rad(main->ray->pa));
	}
}

void	handle_key_press_drc(int keycode, t_main *main)
{
	if (keycode == 53)
		exit (0);
	handle_key_press_dgr(keycode, main);
	if (keycode == 0)
	{
		main->ray->new_px += cos(deg_to_rad(main->ray->pa + 90)) * 10;
		main->ray->new_py -= sin(deg_to_rad(main->ray->pa + 90)) * 10;
	}
	if (keycode == 2)
	{
		main->ray->new_px += cos(deg_to_rad(main->ray->pa - 90)) * 10;
		main->ray->new_py -= sin(deg_to_rad(main->ray->pa - 90)) * 10;
	}
	if (keycode == 13)
	{
		main->ray->new_px += main->ray->pdx * 10;
		main->ray->new_py += main->ray->pdy * 10;
	}
	if (keycode == 1)
	{
		main->ray->new_px -= main->ray->pdx * 10;
		main->ray->new_py -= main->ray->pdy * 10;
	}
}

void	draw_all(t_main *main, int new_block_x, int new_block_y)
{
	if (main->map->new_map[new_block_y * main->ray->width + new_block_x] == 0
		&& main->map->new_map[((int)main->ray->new_py / 64) * main->ray->width
			+ (int)main->ray->new_px / 64] == 0)
	{
		main->ray->px = main->ray->new_px;
		main->ray->py = main->ray->new_py;
	}
	draw_background(main);
	draw_wall(main, main->image_w->pixel_array);
	mlx_put_image_to_window(main->mlx_ptr, main->win_ptr, main->img_ptr, 0, 0);
}

int	handle_key_press(int keycode, t_main *main)
{
	int	new_block_x;
	int	new_block_y;

	main->ray->new_px = main->ray->px;
	main->ray->new_py = main->ray->py;
	handle_key_press_drc(keycode, main);
	if (keycode == 1)
	{
		new_block_x = (main->ray->new_px - main->ray->pdx * 60) / 64;
		new_block_y = (main->ray->new_py - main->ray->pdy * 60) / 64;
	}
	else if (keycode == 13)
	{
		new_block_x = (main->ray->new_px + main->ray->pdx * 60) / 64;
		new_block_y = (main->ray->new_py + main->ray->pdy * 60) / 64;
	}
	else
	{
		new_block_x = (int)main->ray->new_px / 64;
		new_block_y = (int)main->ray->new_py / 64;
	}
	draw_all(main, new_block_x, new_block_y);
	return (0);
}

void	mlx_func(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	main->win_ptr = mlx_new_window(main->mlx_ptr, 1920, 1080, "Cub3D");
	main->img_ptr = mlx_new_image(main->mlx_ptr, 1920, 1080);
	main->data = mlx_get_data_addr(main->img_ptr, &main->bits_per_pixel,
			&main->size_line, &main->endian);
	draw_background(main);
	draw_wall(main, main->image_w->pixel_array);
	mlx_hook(main->win_ptr, 2, 1L << 0, handle_key_press, main);
	mlx_hook(main->win_ptr, 17, 0, close_window, NULL);
	mlx_put_image_to_window(main->mlx_ptr, main->win_ptr, main->img_ptr, 0, 0);
	mlx_loop(main->mlx_ptr);
}
