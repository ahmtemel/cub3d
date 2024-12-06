/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 06:46:13 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 23:26:28 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static inline
char	*ft_sub(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (len - start) + 1);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (j < (len - start))
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_get_word(const char *str, char c, int word)
{
	static size_t	i = 0;
	static size_t	j = 0;
	int				len;
	char			*result;

	while (str[i] && str[i] == c)
		i++;
	j = i;
	while (str[i])
	{
		if (str[i] == c)
		{
			result = ft_sub(str, j, i);
			if (word == 0)
				i = 0;
			return (result);
		}
		i++;
	}
	result = ft_sub(str, j, i);
	i = 0;
	return (result);
}

static inline
int	ft_count(const char *str, char c)
{
	size_t	num_of_words;
	size_t	i;

	if (!str[0])
		return (0);
	num_of_words = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
		{
			num_of_words++;
			while (str[i] && str[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (str[i - 1] != c)
		num_of_words++;
	return (num_of_words);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		num_of_words;
	size_t	i;

	if (!s)
		return (NULL);
	num_of_words = ft_count(s, c);
	result = (char **)malloc(sizeof(char *) * (num_of_words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (num_of_words--)
	{
		result[i] = ft_get_word(s, c, num_of_words);
		if (!result[i])
			return (ft_deallocate(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
