/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:48:40 by bswag             #+#    #+#             */
/*   Updated: 2020/12/22 17:18:20 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		parse_precision(const char *format, int *precision, va_list ap)
{
	int		i;

	i = 0;
	*precision = -1;
	if (format[i] == '.')
	{
		*precision = 0;
		i++;
		if (ft_isdigit(format[i]))
		{
			*precision = ft_atoi(&format[i]);
			while (ft_isdigit(format[++i]))
				;
		}
		else if (format[i] == '*')
		{
			*precision = va_arg(ap, int);
			i++;
		}
	}
	return (i);
}
