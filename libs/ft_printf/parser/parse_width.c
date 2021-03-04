/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:04:34 by bswag             #+#    #+#             */
/*   Updated: 2020/12/22 16:57:53 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		parse_width(const char *format, t_format *frmt, va_list ap)
{
	int		i;
	int		arg;

	i = 0;
	frmt->width = 0;
	if (ft_isdigit(format[i]))
	{
		frmt->width = ft_atoi(format);
		while (ft_isdigit(format[++i]))
			;
	}
	else if (format[i] == '*')
	{
		arg = va_arg(ap, int);
		if (arg < 0)
		{
			frmt->width = -1 * arg;
			frmt->flags = frmt->flags | FLAG_MINUS;
		}
		else
			frmt->width = arg;
		i++;
	}
	return (i);
}
