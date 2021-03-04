/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:02:21 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:16:40 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	process_char(t_format *frmt, int arg)
{
	if (frmt->width != 0)
		frmt->length = frmt->width;
	else
		frmt->length = 1;
	if (!(frmt->flags & FLAG_MINUS))
		ft_write_param(&(frmt->width), 1, \
				(frmt->flags & FLAG_ZERO) ? '0' : ' ');
	write(1, &arg, 1);
	if (frmt->flags & FLAG_MINUS)
		ft_write_param(&(frmt->width), 1, ' ');
}
