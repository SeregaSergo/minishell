/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:50:29 by bswag             #+#    #+#             */
/*   Updated: 2020/11/15 16:22:43 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	n_l;
	int	i;
	int max_len;

	n_l = (int)ft_strlen(needle);
	i = 0;
	if (n_l == 0)
		return (char *)haystack;
	max_len = len - n_l + 1;
	while (*haystack && (i < max_len))
	{
		if ((*haystack == *needle) && (ft_strncmp(haystack, needle, n_l) == 0))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
