/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:09:26 by bswag             #+#    #+#             */
/*   Updated: 2020/11/17 14:08:47 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int base, int pow)
{
	int	result;

	result = 1;
	if (pow < 0)
		return (0);
	while ((pow--) > 0)
		result *= base;
	return (result);
}

static int	ft_get_size(int n)
{
	int	i;
	int	del;

	if (!n)
		return (1);
	i = 1;
	del = 10;
	while ((n /= del) != 0)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	int		size_n;
	char	*ptr;
	int		i;
	int		minus;

	minus = 0;
	i = 0;
	if (n < 0)
		minus = 1;
	size_n = ft_get_size(n);
	ptr = (char *)malloc(size_n + minus + 1);
	if (!ptr)
		return (NULL);
	if (minus)
		ptr[i++] = '-';
	ptr[size_n + minus] = '\0';
	i += size_n - 1;
	while (size_n--)
	{
		ptr[i--] = '0' + (ft_pow(-1, minus) * (n % 10));
		n /= 10;
	}
	return (ptr);
}
