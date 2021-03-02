/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:04:08 by bswag             #+#    #+#             */
/*   Updated: 2020/12/21 15:04:30 by bswag            ###   ########.fr       */
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

static int	ft_get_size(int n, int base)
{
	int	i;

	if (!n)
		return (1);
	i = 1;
	while ((n /= base) != 0)
		i++;
	return (i);
}

char		*ft_itoa_base(int n, int base)
{
	int		size_n;
	char	*ptr;
	int		i;
	int		minus;
	int		tmp;

	minus = 0;
	i = 0;
	if (n < 0)
		minus = 1;
	size_n = ft_get_size(n, base);
	if (!(ptr = (char *)malloc(size_n + minus + 1)))
		return (NULL);
	if (minus)
		ptr[i++] = '-';
	ptr[size_n + minus] = '\0';
	i += size_n - 1;
	while (size_n--)
	{
		tmp = (ft_pow(-1, minus) * (n % base));
		ptr[i--] = ((tmp > 9) ? 'W' : '0') + tmp;
		n /= base;
	}
	return (ptr);
}
