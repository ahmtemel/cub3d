/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:01:00 by ahmtemel          #+#    #+#             */
/*   Updated: 2024/03/06 21:53:40 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	allocation_exit(t_main *main)
{
	(void)main;
	printf("Allocation Error\n");
	exit(1);
}

void	check_file_name(t_main *main, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		wrong_argument_exit(main, 11);
	if (name[len - 1] != 'b' || name[len - 2] != 'u' || name[len - 3] != 'c'
		|| name[len - 4] != '.')
		wrong_argument_exit(main, 11);
}

char	**handle_texture(const char *s, t_main *map_data)
{
	char	**result;
	char	**raw;
	int		i;

	result = malloc(sizeof(char *) * 3);
	if (!result)
		allocation_exit(map_data);
	raw = ft_split(s, ' ');
	if (!raw[0][0] || !raw[1][0])
	{
		free_double_char(raw);
		free(result);
		wrong_map_exit(map_data, 23);
	}
	result[0] = ft_strdup(raw[0]);
	free_double_char(raw);
	result[2] = NULL;
	i = 0;
	while (s[i] && s[i] != '.' && s[i + 1] != '/')
		i++;
	result[1] = ft_strtrim(&s[i], "\n");
	return (result);
}

char	**handle_fc(const char *s, t_main *main)
{
	char	**result;
	char	**raw;
	char	**first_index;
	int		i;

	result = malloc(sizeof(char *) * 5);
	if (!result)
		allocation_exit(main);
	raw = ft_split(s, ',');
	i = 0;
	while (raw[i])
		i++;
	first_index = ft_split(raw[0], ' ');
	if (i != 3 || !first_index[1])
	{
		free(result);
		wrong_map_exit(main, 21);
	}
	result[0] = ft_strdup(first_index[0]);
	result[1] = ft_strdup(first_index[1]);
	result[2] = ft_strtrim(raw[1], " \n");
	result[3] = ft_strtrim(raw[2], " \n");
	free_double_char(raw);
	free_double_char(first_index);
	return (result);
}

void	set_ceiling_floor(t_main *main, char **splitted, int flag)
{
	int	count;

	count = 0;
	if (flag == 1)
		if_flag_one(splitted, main, flag);
	while (splitted[count] != NULL)
		count++;
	if (splitted[0][0] == 'F' && count == 4)
	{
		main->f[0] = ft_atoi(splitted[1]);
		main->f[1] = ft_atoi(splitted[2]);
		main->f[2] = ft_atoi(splitted[3]);
		main->color_f = (main->f[0] << 16 | main->f[1] << 8 | main->f[2]);
	}
	else if (splitted[0][0] == 'C' && count == 4)
	{
		main->c[0] = ft_atoi(splitted[1]);
		main->c[1] = ft_atoi(splitted[2]);
		main->c[2] = ft_atoi(splitted[3]);
		main->color_c = (main->c[0] << 16 | main->c[1] << 8 | main->c[2]);
	}
	else
		wrong_map_exit(main, 21);
}
