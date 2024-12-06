/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assault_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:32:01 by ahmtemel          #+#    #+#             */
/*   Updated: 2024/03/06 21:43:03 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	find_height(char **map)
{
	int	r;

	while (map[r])
		r++;
	return (r);
}

int	find_width(char **map)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n')
			j++;
		if (j > c)
			c = j;
		i++;
	}
	return (c);
}

int	*init_new_map(t_main *main)
{
	int	*map;

	map = malloc(sizeof(int) * main->ray->maps);
	return (map);
}

void	fill_map(t_main *main, int *new_map)
{
	int		i;
	int		j;
	int		width;
	char	**map;

	i = 0;
	j = 0;
	width = main->ray->width;
	map = main->map->map;
	while (i < main->ray->height)
	{
		j = 0;
		while (j < main->ray->width)
		{
			if (j < ft_strlen(map[i]))
				new_map[(i * width) + j] = map[i][j] - 48;
			else
				new_map[(i * width) + j] = 1;
			j++;
		}
		i++;
	}
}

void	assault_map(t_main *main)
{
	int	*new_map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	main->ray->width = find_width(main->map->map);
	main->ray->height = find_height(main->map->map);
	main->ray->maps = main->ray->width * main->ray->height;
	new_map = init_new_map(main);
	fill_map(main, new_map);
	main->map->new_map = new_map;
}
