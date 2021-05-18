/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:59:00 by bswag             #+#    #+#             */
/*   Updated: 2021/05/01 20:29:45 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(unsigned long long int n, int base)
{
	int	i;

	if (!n)
		return (1);
	i = 1;
	n /= base;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*ft_lutoa_base(unsigned long long int n, int base)
{
	char	*ptr;
	int		i;
	int		tmp;

	i = ft_get_size(n, base);
	ptr = (char *)malloc(i + 1);
	if (!ptr)
		return (NULL);
	ptr[i--] = '\0';
	while (i > -1)
	{
		tmp = (n % base);
		if (tmp > 9)
			ptr[i] = 'W' + tmp;
		else
			ptr[i] = '0' + tmp;
		n /= base;
		i--;
	}
	return (ptr);
}
