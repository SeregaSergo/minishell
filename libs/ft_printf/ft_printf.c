/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:57:21 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:31:14 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_format	frmt;
	int			length;

	va_start(ap, format);
	length = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			format += ft_parser(format, &frmt, ap);
			ft_processor(&frmt, ap);
			if (frmt.type == '\0')
				break ;
			length += frmt.length;
		}
		else
		{
			write(1, format++, 1);
			length++;
		}
	}
	va_end(ap);
	return (length);
}
