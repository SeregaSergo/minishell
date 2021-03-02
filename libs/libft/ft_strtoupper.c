/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:24:20 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:28:33 by bswag            ###   ########.fr       */
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
	if (!(ptr = (char *)malloc(size + 1)))
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
