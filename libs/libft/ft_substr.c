/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 19:33:57 by bswag             #+#    #+#             */
/*   Updated: 2020/11/16 14:45:04 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
		ft_strlcpy(ptr, &s[start], size_of_sub_str + 1);
		return (ptr);
	}
	else
		return (NULL);
}
