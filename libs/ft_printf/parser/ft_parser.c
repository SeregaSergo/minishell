/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:28:12 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:14:53 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_parser(const char *format, t_format *frmt, va_list ap)
{
	int	i;

	i = 0;
	i += parse_flags(&format[i], &(frmt->flags));
	i += parse_width(&format[i], frmt, ap);
	i += parse_precision(&format[i], &(frmt->precision), ap);
	i += parse_type(&format[i], &(frmt->type));
	return (i);
}
