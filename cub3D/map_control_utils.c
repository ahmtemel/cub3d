/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:06:21 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 21:53:40 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_ceiling_floor(t_main *main, char *trimmed)
{
	int		i;
	int		j;
	int		flag;
	char	**splitted;

	flag = 0;
	splitted = ft_split_special(trimmed, main);
	i = 0;
	while (splitted[++i])
	{
		if (flag == 1)
			break ;
		j = 0;
		while (splitted[i][j])
		{
			if ((!ft_isdigit(splitted[i][j]) || i > 3))
			{
				flag = 1;
				break ;
			}
			j++;
		}
	}
	set_ceiling_floor(main, splitted, flag);
	free_double_char(splitted);
}

char	*get_path(char *trimmed, t_main *main)
{
	int	i;

	i = 2;
	while (trimmed[i] && trimmed[i] == ' '
		&& (trimmed[i] != '.' || trimmed[i + 1] != '/'))
		i++;
	if (!trimmed[i] || ft_strlen(&trimmed[i]) < 3
		|| trimmed[i] != '.')
	{
		free(trimmed);
		wrong_map_exit(main, 23);
	}
	i++;
	return (ft_strtrim(&trimmed[i - 1], "\n"));
}

void	get_textures(t_main *main, char *trimmed)
{
	int		flag;
	char	**spltd;

	flag = 0;
	spltd = ft_split_special(trimmed, main);
	if (!spltd[1])
	{
		free_double_char(spltd);
		wrong_map_exit(main, 23);
	}
	if (spltd[0][0] == 'E' && spltd[0][1] == 'A' && !main->ea)
		main->ea = get_path(trimmed, main);
	else if (spltd[0][0] == 'W' && spltd[0][1] == 'E' && !main->we)
		main->we = get_path(trimmed, main);
	else if (spltd[0][0] == 'N' && spltd[0][1] == 'O' && !main->no)
		main->no = get_path(trimmed, main);
	else if (spltd[0][0] == 'S' && spltd[0][1] == 'O' && !main->so)
		main->so = get_path(trimmed, main);
	else
		flag = 1;
	free_double_char(spltd);
	if (flag == 1)
		wrong_map_exit(main, 20);
}

void	fill_info(t_main *main, char *line)
{
	int		i;
	char	*trm;

	i = 0;
	while (is_it_ws(line[i]))
		i++;
	trm = ft_strdup(&line[i]);
	if ((trm[0] == 'C' || trm[0] == 'F') && main->floor == NULL
		&& (trm[1] == ' ' && main->ceiling == NULL))
		get_ceiling_floor(main, trm);
	else if (((trm[0] == 'E' && trm[1] == 'A' && main->ea == NULL)
			|| (trm[0] == 'W' && trm[1] == 'E' && main->we == NULL)
			|| (trm[0] == 'N' && trm[1] == 'O' && main->no == NULL)
			|| (trm[0] == 'S' && trm[1] == 'O' && main->so == NULL))
		&& is_it_ws(trm[2]))
		get_textures(main, trm);
	else
	{
		free(trm);
		wrong_map_exit(main, 20);
	}
	free(trm);
	free(line);
}

void	get_info(t_main *main, int flag, char **new_map)
{
	int	i;
	int	j;

	free_double_char(main->whole_map);
	main->floor = NULL;
	main->ceiling = NULL;
	main->whole_map = new_map;
	if (flag == 2)
		wrong_map_exit(main, 22);
	i = -1;
	while (++i < 6)
		fill_info(main, main->whole_map[i]);
	main->map->map = malloc(sizeof(char *) * (main->line_count - 6 + 1));
	if (!main->map)
		allocation_exit(main);
	j = 0;
	while (main->whole_map[i])
		main->map->map[j++] = ft_strdup(main->whole_map[i++]);
	main->map->map[j] = NULL;
}
