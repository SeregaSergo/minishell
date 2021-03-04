/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_uxx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:18:31 by bswag             #+#    #+#             */
/*   Updated: 2020/12/24 17:25:12 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	analize_length(t_format *frmt, int len_word, char *prefix)
{
	int		length_spw;

	frmt->length = len_word;
	if ((frmt->precision) > (frmt->length))
		frmt->length = frmt->precision;
	if (prefix != NULL)
		frmt->length += 2;
	length_spw = frmt->length;
	if ((frmt->width) > (frmt->length))
		frmt->length = frmt->width;
	return (length_spw);
}

static char	*get_prefix(t_format *frmt)
{
	if (frmt->flags & FLAG_SHARP)
	{
		if (frmt->type == 'x')
			return ("0x");
		else if (frmt->type == 'X')
			return ("0X");
	}
	return (NULL);
}

static void	handle_zero_flag(t_format *frmt, char *prefix)
{
	if (frmt->flags & FLAG_MINUS)
		return ;
	if (frmt->precision != -1)
		return ;
	if (prefix != NULL && frmt->width > 1)
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

void		process_uxx(t_format *frmt, unsigned int arg)
{
	char	*prefix;
	int		word_size;
	char	*word;

	prefix = get_prefix(frmt);
	if (frmt->type != 'u')
		word = ft_lutoa_base(arg, 16);
	else
		word = ft_lutoa_base(arg, 10);
	if (frmt->type == 'X')
		word = ft_strtoupper(word);
	word = check_null(word, frmt);
	if (frmt->flags & FLAG_ZERO)
		handle_zero_flag(frmt, prefix);
	word_size = analize_length(frmt, ft_strlen(word), prefix);
	if (!(frmt->flags & FLAG_MINUS))
		ft_write_param(&(frmt->width), word_size, ' ');
	if (prefix != NULL)
		write(1, prefix, 2);
	ft_write_param(&(frmt->precision), ft_strlen(word), '0');
	write(1, word, ft_strlen(word));
	free(word);
	if (frmt->flags & FLAG_MINUS)
		ft_write_param(&(frmt->width), word_size, ' ');
}
