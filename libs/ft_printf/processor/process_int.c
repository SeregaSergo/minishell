/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:17:04 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:26:16 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	analize_length(t_format *frmt, int len_word, char sign)
{
	int		length_spw;

	frmt->length = len_word;
	if ((frmt->precision) > (frmt->length))
		frmt->length = frmt->precision;
	if (sign == '-' || frmt->flags & FLAG_SPACE || frmt->flags & FLAG_PLUS)
		frmt->length += 1;
	length_spw = frmt->length;
	if ((frmt->width) > (frmt->length))
		frmt->length = frmt->width;
	return (length_spw);
}

static char	get_sign(t_format *frmt, int arg)
{
	if (arg < 0)
		return ('-');
	if (frmt->flags & FLAG_PLUS)
		return ('+');
	if (frmt->flags & FLAG_SPACE)
		return (' ');
	return ('\0');
}

static void	handle_zero_flag(t_format *frmt, char sign)
{
	if (frmt->flags & FLAG_MINUS)
		return ;
	if (frmt->precision > -1)
		return ;
	if (frmt->precision < -1)
		frmt->precision *= -1;
	if (sign == '\0')
		frmt->precision = frmt->width;
	else if (frmt->width != 0)
		frmt->precision = frmt->width - 1;
}

static char	*check_null(char *word, t_format *frmt)
{
	char *ptr;

	if (word[0] == '0' && frmt->precision == 0)
	{
		free(word);
		ptr = (char *)malloc(sizeof(char) * 1);
		ptr[0] = '\0';
		return (ptr);
	}
	else
		return (word);
}

void		process_int(t_format *frmt, long int arg)
{
	char	sign;
	int		word_size;
	char	*word;

	sign = get_sign(frmt, arg);
	if (arg < 0)
		arg *= -1;
	word = ft_lutoa_base(arg, 10);
	word = check_null(word, frmt);
	if (frmt->flags & FLAG_ZERO)
		handle_zero_flag(frmt, sign);
	word_size = analize_length(frmt, ft_strlen(word), sign);
	if (!(frmt->flags & FLAG_MINUS))
		ft_write_param(&(frmt->width), word_size, ' ');
	if (sign != '\0')
		write(1, &sign, 1);
	ft_write_param(&(frmt->precision), ft_strlen(word), '0');
	write(1, word, ft_strlen(word));
	free(word);
	if (frmt->flags & FLAG_MINUS)
		ft_write_param(&(frmt->width), word_size, ' ');
}
