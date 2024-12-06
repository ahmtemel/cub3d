/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:08:16 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 21:10:46 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	**ft_split_special(const char *s, t_main *main)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	if ((s[0] == 'F' || s[0] == 'C') && s[1] == ' ')
	{
		result = handle_fc(s, main);
		result[4] = NULL;
	}
	else
		result = handle_texture(s, main);
	i = -1;
	while (result[++i])
	{
		if (!result[i][0])
			wrong_argument_exit(main, 21);
	}
	return (result);
}

void	if_flag_one(char **splitted, t_main *main, int flag)
{
	free_double_char(splitted);
	wrong_map_exit(main, 21);
}
