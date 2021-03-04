/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:07:19 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:27:37 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	analize_length(t_format *frmt, int len_word)
{
	int		length_w;

	frmt->length = len_word;
	if (frmt->precision > -1 && frmt->precision < len_word)
		frmt->length = frmt->precision;
	length_w = frmt->length;
	if ((frmt->width) > (frmt->length))
		frmt->length = frmt->width;
	return (length_w);
}

void		process_str(t_format *frmt, char *arg)
{
	int		word_size;

	if (arg == NULL)
		arg = "(null)";
	word_size = analize_length(frmt, ft_strlen(arg));
	if (!(frmt->flags & FLAG_MINUS))
		ft_write_param(&(frmt->width), word_size, ' ');
	write(1, arg, word_size);
	if (frmt->flags & FLAG_MINUS)
		ft_write_param(&(frmt->width), word_size, ' ');
}
