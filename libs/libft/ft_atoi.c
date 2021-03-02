/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:23:54 by bswag             #+#    #+#             */
/*   Updated: 2020/12/21 22:29:04 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned long long int	ft_pow(int base, int pow)
{
	unsigned long long int		result;

	result = 1;
	if (pow < 0)
		return (0);
	while (pow > 0)
	{
		result *= base;
		pow--;
	}
	return (result);
}

static int						ft_get_pow(unsigned long long int number)
{
	int result;

	result = 0;
	while (number > 9)
	{
		number /= 10;
		result++;
	}
	return (result);
}

static int						ft_max_pow_lli(void)
{
	int						size_lli;
	unsigned long long int	max_val;

	size_lli = sizeof(long long int) * 8 - 1;
	max_val = ft_pow(2, size_lli);
	return (ft_get_pow(max_val));
}

static int						ft_over(int i)
{
	if (i == -1)
		return (0);
	else
		return (-1);
}

int								ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int i;
	int	max_long;

	result = 0;
	sign = 1;
	i = 0;
	max_long = ft_max_pow_lli();
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (i > max_long)
			return (ft_over(sign));
	}
	return (sign * result);
}
