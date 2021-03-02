/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:43:57 by bswag             #+#    #+#             */
/*   Updated: 2020/11/15 20:18:18 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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
