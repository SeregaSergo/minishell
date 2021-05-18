/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 18:03:56 by bswag             #+#    #+#             */
/*   Updated: 2021/05/01 20:27:22 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_rvrs_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr_dst;
	char	*ptr_src;
	int		i;

	if (dst == NULL && src == NULL)
		return (dst);
	i = n - 1;
	ptr_dst = (char *)dst;
	ptr_src = (char *)src;
	while (n--)
	{
		ptr_dst[i] = ptr_src[i];
		i--;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst > src)
		return (ft_rvrs_memcpy(dst, src, len));
	else
		return (ft_memcpy(dst, src, len));
}
