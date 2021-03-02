/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:59:00 by bswag             #+#    #+#             */
/*   Updated: 2020/12/22 15:56:44 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(unsigned long long int n, int base)
{
	int	i;

	if (!n)
		return (1);
	i = 1;
	while ((n /= base) != 0)
		i++;
	return (i);
}

char		*ft_lutoa_base(unsigned long long int n, int base)
{
	char	*ptr;
	int		i;
	int		tmp;

	i = ft_get_size(n, base);
	if (!(ptr = (char *)malloc(i + 1)))
		return (NULL);
	ptr[i--] = '\0';
	while (i > -1)
	{
		tmp = (n % base);
		ptr[i] = ((tmp > 9) ? 'W' : '0') + tmp;
		n /= base;
		i--;
	}
	return (ptr);
}
