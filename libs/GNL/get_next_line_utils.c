/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:29:15 by bswag             #+#    #+#             */
/*   Updated: 2021/02/01 22:10:25 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		size_of_sub_str;

	if (s)
	{
		size_of_sub_str = ft_strlen(s) - start;
		if (size_of_sub_str < 0)
			size_of_sub_str = 0;
		if (size_of_sub_str > (int)len)
			size_of_sub_str = len;
		ptr = (char *)malloc(size_of_sub_str + 1);
		if (!ptr)
			return (NULL);
		gnl_strlcpy(ptr, &s[start], size_of_sub_str + 1);
		return (ptr);
	}
	else
		return (NULL);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*ptr;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	gnl_strlcpy(ptr, s1, len1 + 1);
	gnl_strlcpy(&ptr[len1], s2, len2 + 1);
	return (ptr);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*ptr;

	ptr = src;
	if (dstsize != 0 && dst && src)
	{
		dstsize--;
		while (dstsize && *ptr)
		{
			*dst = *ptr;
			dstsize--;
			ptr++;
			dst++;
		}
		*dst = '\0';
	}
	if (src)
		return (ft_strlen(src));
	else
		return (0);
}

int		gnl_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != c)
	{
		if (!(s[i]))
			return (-1);
		i++;
	}
	return (i);
}
