/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:27:50 by bswag             #+#    #+#             */
/*   Updated: 2020/11/17 19:27:21 by bswag            ###   ########.fr       */
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
	int i;

	if (!n)
		return (1);
	i = 1;
	while ((n /= base) != 0)
		i++;
	return (i);
}

void		ft_putnbr_fd(int n, int fd)
{
	int	size;
	int	minus;
	int	del;

	size = ft_get_size(n, 10);
	minus = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		minus = -1;
	}
	while (size--)
	{
		del = ft_pow(10, size);
		ft_putchar_fd('0' + (minus * (n / del)), fd);
		n %= del;
	}
}
