/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:42:48 by bswag             #+#    #+#             */
/*   Updated: 2020/11/19 20:56:14 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_find_next_c(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void		ft_clear(char **list, int i)
{
	char	**ptr;

	ptr = list;
	while (i--)
	{
		free(*ptr);
		ptr++;
	}
	free(list);
}

static int		ft_count_words(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			i++;
			s += ft_find_next_c(s, c);
		}
	}
	return (i);
}

static char		**ft_fill_list(char const *s, char c, char **list)
{
	int		i;
	int		flag;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if ((flag = ft_find_next_c(s, c)))
		{
			list[i] = ft_substr(s, 0, flag);
			if (!list[i])
			{
				ft_clear(list, i);
				return (NULL);
			}
			i++;
			s += flag;
		}
	}
	list[i] = NULL;
	return (list);
}

char			**ft_split(char const *s, char c)
{
	char	**list;
	int		nmbr_of_words;

	if (!s)
		return (NULL);
	nmbr_of_words = ft_count_words(s, c);
	list = malloc(sizeof(void *) * (nmbr_of_words + 1));
	if (!list)
		return (NULL);
	list = ft_fill_list(s, c, list);
	return (list);
}
