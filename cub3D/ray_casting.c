/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:52:27 by ahmtemel          #+#    #+#             */
/*   Updated: 2024/03/06 21:14:36 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	horizontal_up_down(t_ray *ray)
{
	ray->check = 0;
	ray->tan = 1.0 / ray->tan;
	ray->dish = 100000;
	if (sin(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->ry = (((int)ray->py >> 6) << 6) - 0.0001;
		ray->rx = ((ray->py - ray->ry) * ray->tan) + ray->px;
		ray->yo = -64;
		ray->xo = -(ray->yo * ray->tan);
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->ry = (((int)ray->py >> 6) << 6) + 64;
		ray->rx = ((ray->py - ray->ry) * ray->tan) + ray->px;
		ray->yo = 64;
		ray->xo = -(ray->yo * ray->tan);
	}
	else
	{
		ray->rx = ray->px;
		ray->ry = ray->py;
		ray->check = ray->height;
	}
}

void	fill_float_array(t_main *main)
{
	t_ray	*ray;

	ray = main->ray;
	if (ray->disv < ray->dish)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->dish = ray->disv;
		if (cos(deg_to_rad(ray->ra)) > 0.001)
			ray->drc[ray->i] = 'N';
		else
			ray->drc[ray->i] = 'S';
	}
	else
	{
		if (sin(deg_to_rad(ray->ra)) > 0.001)
			ray->drc[ray->i] = 'W';
		else
			ray->drc[ray->i] = 'E';
	}
	ray->ca = fix_ang(ray->pa - ray->ra);
	ray->dish = ray->dish * cos(deg_to_rad(ray->ca));
	ray->ray[ray->i] = ray->dish;
	ray->ray_xy[ray->i][0] = ray->ry;
	ray->ray_xy[ray->i][1] = ray->rx;
}

void	horizontal_loop(t_main *main)
{
	t_ray	*ray;

	ray = main->ray;
	while (ray->check < ray->height)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * ray->width + ray->mx;
		if (ray->mp > 0 && ray->mp < ray->width * ray->height \
				&& main->map->new_map[ray->mp] == 1)
		{
			ray->check = ray->height;
			ray->dish = cos(deg_to_rad(ray->ra)) * (ray->rx - ray->px) \
				- sin(deg_to_rad(ray->ra)) * (ray->ry - ray->py);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->check += 1;
		}
	}
}

float	*ray_casting(t_main *main)
{
	t_ray	*ray;

	ray = main->ray;
	ray->ra = fix_ang(ray->pa + 30);
	while (ray->i < 60)
	{
		vertical_left_right(ray);
		vertical_loop(main);
		horizontal_up_down(ray);
		horizontal_loop(main);
		fill_float_array(main);
		(ray->i)++;
		ray->ra = fix_ang(ray->ra -1);
	}
	ray->i = 0;
	ray->drc[60] = '\0';
	return (ray->ray);
}
