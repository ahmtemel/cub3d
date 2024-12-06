/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:45 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/07 00:18:22 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_clean_map(t_main *main, char **new_map, int count)
{
	int	i;
	int	j;
	int	flag;

	(void)count;
	i = -1;
	j = 0;
	flag = 0;
	while (main->whole_map[++i])
	{
		if (j > 6 && is_line_empty(main->whole_map[i]))
			flag = 1;
		if (!is_line_empty(main->whole_map[i]))
		{
			if (flag == 1)
			{
				flag = 2;
				break ;
			}
			new_map[j++] = ft_strdup(main->whole_map[i]);
		}
	}
	get_info(main, flag, new_map);
}

void	get_map(t_main *main)
{
	int	i;
	int	fd;

	main->line_count = get_line_count(main);
	main->whole_map = malloc(sizeof(char *) * (main->line_count + 1));
	if (!(main->whole_map))
		allocation_exit(main);
	fd = open(main->map_path, O_RDONLY);
	if (fd < 0)
		wrong_argument_exit(main, 11);
	i = -1;
	while (++i < main->line_count)
		main->whole_map[i] = get_next_line(fd);
	main->whole_map[i] = NULL;
	check_empty_lines(main, main->whole_map);
	main->direction = '0';
	close(fd);
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

void	clear_map(t_main *main)
{
	int		i;
	int		count;
	char	**spaceless;

	i = -1;
	count = 0;
	if (main->line_count == 0)
		wrong_map_exit(main, 22);
	while (++i < main->line_count)
	{
		if (!is_line_empty(main->whole_map[i]))
			count++;
	}
	main->line_count = count;
	spaceless = malloc(sizeof(char *) * (count + 1));
	if (!spaceless)
		allocation_exit(main);
	main->we = NULL;
	main->no = NULL;
	main->so = NULL;
	main->ea = NULL;
	spaceless[count] = NULL;
	set_clean_map(main, spaceless, count);
}

void	check_rgb(t_main *main)
{
	if (main->c[0] < 0 || main->c[0] > 255 || main->c[1] < 0 || main->c[1] > 255
		|| main->c[2] < 0 || main->c[2] > 255 || main->f[0] < 0
		|| main->f[0] > 255 || main->f[1] < 0 || main->f[1] > 255
		|| main->f[2] < 0 || main->f[2] > 255)
		wrong_map_exit(main, 21);
}
