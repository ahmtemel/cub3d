/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:46:55 by rdemiray          #+#    #+#             */
/*   Updated: 2024/03/07 00:18:12 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_map_characters(t_main *main, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((!is_it_ws(map[i][j])) && map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != 'S')
				wrong_map_exit(main, 25);
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S')
			{
				if (main->direction == '0')
					main->direction = map[i][j];
				else
					wrong_map_exit(main, 26);
			}
		}
	}
	if (main->direction == '0')
		wrong_map_exit(main, 27);
}

void	check_horizantal(t_main *main, char **map, int i, int j)
{
	int	backup;

	backup = j;
	while (map[i][j] != '1')
	{
		if (is_it_ws(map[i][j]) || map[i][j] == '\0')
			wrong_map_exit(main, 28);
		j++;
	}
	j = backup;
	while (map[i][j] != '1')
	{
		if (i == 0 || is_it_ws(map[i][j]))
			wrong_map_exit(main, 28);
		j--;
	}
}

void	check_vertical(t_main *main, char **map, int i, size_t j)
{
	int	backup;

	backup = i;
	while (map[i][j] != '1')
	{
		if (!map[i + 1] || ft_strlen(map[i + 1]) < j || is_it_ws(map[i][j]))
			wrong_map_exit(main, 28);
		i++;
	}
	i = backup;
	while (map[i][j] != '1')
	{
		if (i == 0 || ft_strlen(map[i - 1]) < j)
			wrong_map_exit(main, 28);
		if (is_it_ws(map[i][j]))
			wrong_map_exit(main, 28);
		i--;
	}
}

void	check_borders(t_main *map_data, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == map_data->direction)
			{
				check_vertical(map_data, map, i, j);
				check_horizantal(map_data, map, i, j);
			}
		}
	}
}

void	check_map(t_main *main)
{
	int	i;

	get_map(main);
	clear_map(main);
	check_rgb(main);
	check_map_characters(main, main->map->map);
	check_borders(main, main->map->map);
}
