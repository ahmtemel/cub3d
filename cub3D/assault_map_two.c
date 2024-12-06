/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assault_map_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:46:53 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 20:51:36 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	fov_func(t_main *main, int y, int x)
{
	if (main->map->map[y][x] == 'N')
		main->ray->p_fov = 'N';
	else if (main->map->map[y][x] == 'W')
		main->ray->p_fov = 'W';
	else if (main->map->map[y][x] == 'S')
		main->ray->p_fov = 'S';
	else if (main->map->map[y][x] == 'E')
		main->ray->p_fov = 'E';
}

void	player_position(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (main->map->map[i])
	{
		j = 0;
		while (main->map->map[i][j])
		{
			if (main->map->map[i][j] == 'N' || main->map->map[i][j] == 'S'
				|| main->map->map[i][j] == 'W' || main->map->map[i][j] == 'E')
			{
				fov_func(main, i, j);
				main->ray->player_y = i;
				main->ray->player_x = j;
				main->map->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}
