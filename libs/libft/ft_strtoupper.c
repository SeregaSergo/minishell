/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:24:20 by bswag             #+#    #+#             */
/*   Updated: 2021/05/01 20:21:17 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char *s)
{
	size_t	size;
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = ft_toupper(s[i]);
		i++;
	}
	ptr[i] = '\0';
	free(s);
	return (ptr);
}
