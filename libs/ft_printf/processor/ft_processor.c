/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 19:59:45 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:17:49 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_processor(t_format *frmt, va_list ap)
{
	frmt->length = 0;
	if (ft_strchr_null("di", frmt->type))
		process_int(frmt, va_arg(ap, int));
	else if (ft_strchr_null("uxX", frmt->type))
		process_uxx(frmt, va_arg(ap, unsigned int));
	else if (frmt->type == 'p')
		process_p(frmt, va_arg(ap, void *));
	else if (frmt->type == 's')
		process_str(frmt, va_arg(ap, char *));
	else if (frmt->type == 'c')
		process_char(frmt, va_arg(ap, int));
	else if (frmt->type == '%')
		process_char(frmt, '%');
}
