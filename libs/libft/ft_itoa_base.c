/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:04:08 by bswag             #+#    #+#             */
/*   Updated: 2021/05/01 20:50:22 by bswag            ###   ########.fr       */
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
	n /= base;
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

int	is_minus(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static void	init(int n, int *minus, int *size_n, int base)
{
	if (n < 0)
		*minus = 1;
	else
		*minus = 0;
	*size_n = ft_get_size(n, base);
}

char	*ft_itoa_base(int n, int base)
{
	int		size_n;
	char	*ptr;
	int		i;
	int		minus;
	int		tmp;

	i = 0;
	init(n, &minus, &size_n, base);
	ptr = (char *)malloc(size_n + minus + 1);
	if (!ptr)
		return (NULL);
	if (minus)
		ptr[i++] = '-';
	ptr[size_n + minus] = '\0';
	i += size_n - 1;
	while (size_n--)
	{
		tmp = (ft_pow(-1, minus) * (n % base));
		if (tmp > 9)
			ptr[i--] = 'W' + tmp;
		else
			ptr[i--] = '0' + tmp;
		n /= base;
	}
	return (ptr);
}
