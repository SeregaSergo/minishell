/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:47:33 by bswag             #+#    #+#             */
/*   Updated: 2020/11/13 19:14:13 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	initial_len;
	size_t	src_len;

	initial_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize >= initial_len)
	{
		ft_strlcpy(dst + initial_len, src, dstsize - initial_len);
		return (initial_len + src_len);
	}
	else
		return (dstsize + src_len);
}
