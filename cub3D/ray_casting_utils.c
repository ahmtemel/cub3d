/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:14:22 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 21:39:31 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}

int	fix_ang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

void	vertical_left_right(t_ray *ray)
{
	ray->check = 0;
	ray->disv = 100000;
	ray->tan = tan(deg_to_rad(ray->ra));
	if (cos(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->rx = (((int)ray->px >> 6) << 6) + 64;
		ray->ry = ((ray->px - ray->rx) * ray->tan) + ray->py;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->tan;
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->rx = (((int)ray->px >> 6) << 6) + -0.0001;
		ray->ry = ((ray->px - ray->rx) * ray->tan) + ray->py;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->tan;
	}
	else
	{
		ray->rx = ray->px;
		ray->ry = ray->py;
		ray->check = ray->width;
	}
}

void	vertical_loop(t_main *main)
{
	t_ray	*ray;

	ray = main->ray;
	while (ray->check < ray->width)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * ray->width + ray->mx;
		if (ray->mp > 0 && ray->mp < ray->width * ray->height \
				&& main->map->new_map[ray->mp] == 1)
		{
			ray->check = ray->width;
			ray->disv = cos(deg_to_rad(ray->ra)) * (ray->rx - ray->px) \
				- sin(deg_to_rad(ray->ra)) * (ray->ry - ray->py);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->check += 1;
		}
	}
	ray->vx = ray->rx;
	ray->vy = ray->ry;
}
