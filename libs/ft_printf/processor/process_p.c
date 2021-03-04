/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:20:56 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:27:04 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	analize_length(t_format *frmt, int len_word)
{
	int		length_spw;

	frmt->length = len_word + 2;
	if ((frmt->precision) > (frmt->length))
		frmt->length = frmt->precision;
	length_spw = frmt->length;
	if ((frmt->width) > (frmt->length))
		frmt->length = frmt->width;
	return (length_spw);
}

static void	handle_zero_flag(t_format *frmt)
{
	if (frmt->flags & FLAG_MINUS)
		return ;
	if (frmt->precision > -1)
		return ;
	if (frmt->width > 1)
		frmt->precision = frmt->width - 2;
	else
		frmt->precision = frmt->width;
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

void		process_p(t_format *frmt, void *arg)
{
	int		word_size;
	char	*word;

	word = ft_lutoa_base((unsigned long long int)arg, 16);
	word = check_null(word, frmt);
	if (frmt->flags & FLAG_ZERO)
		handle_zero_flag(frmt);
	word_size = analize_length(frmt, ft_strlen(word));
	if (!(frmt->flags & FLAG_MINUS))
		ft_write_param(&(frmt->width), word_size, ' ');
	write(1, "0x", 2);
	ft_write_param(&(frmt->precision), ft_strlen(word), '0');
	write(1, word, ft_strlen(word));
	free(word);
	if (frmt->flags & FLAG_MINUS)
		ft_write_param(&(frmt->width), word_size, ' ');
}
