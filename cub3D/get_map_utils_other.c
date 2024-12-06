/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils_other.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:07:31 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/07 00:13:09 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_line_count(t_main *main)
{
	int		fd;
	int		count;
	char	*line;

	main->map_path = ft_strdup(main->map_name);
	if (!main->map_path)
		allocation_exit(main);
	fd = open(main->map_path, O_RDONLY);
	if (fd < 0)
		wrong_argument_exit(main, 11);
	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (count);
}

void	wrong_map_exit(t_main *main, int code)
{
	(void)main;
	if (code == 20)
		printf("Wrong Or Missing Data in .cub File Error\n");
	else if (code == 21)
		printf("Wrong RGB value Error\n");
	else if (code == 22)
		printf("Empty Line In The Map Or Extra Data Error\n");
	else if (code == 23)
		printf("Wrong Texture File Name Error\n");
	else if (code == 24)
		printf("Wrong Character In Line Error\n");
	else if (code == 25)
		printf("Wrong Character In The Map Error\n");
	else if (code == 26)
		printf("Multiple Starting Point Error\n");
	else if (code == 27)
		printf("There Is No Starting Point In The Map Error\n");
	else if (code == 28)
		printf("Map Must Be Covered By Walls Correctly Error\n");
	else if (code == 29)
		printf("Wrong Texture File Error\n");
	exit(code);
}

void	check_empty_lines(t_main *main, char **map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if ((!ft_strnstr(map[i], "WE", ft_strlen(map[i])))
			&& (!ft_strnstr(map[i], "NO", ft_strlen(map[i])))
			&& (!ft_strnstr(map[i], "SO", ft_strlen(map[i])))
			&& (!ft_strnstr(map[i], "EA", ft_strlen(map[i])))
			&& (!ft_strnstr(map[i], "F", ft_strlen(map[i])))
			&& (!ft_strnstr(map[i], "C", ft_strlen(map[i])))
			&& (!ft_strnstr(map[i], "1", ft_strlen(map[i])))
			&& (map[i][0] != '\n'))
			wrong_map_exit(main, 24);
	}
}

void	free_double_char(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr[i]);
	free(ptr);
}

int	is_it_ws(int c)
{
	if (c == 32 || c == 10)
		return (1);
	return (0);
}
