/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:07:14 by bswag             #+#    #+#             */
/*   Updated: 2020/12/18 16:42:08 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static unsigned char	ft_isflag(char c)
{
	if (c == '#')
		return (FLAG_SHARP);
	else if (c == '-')
		return (FLAG_MINUS);
	else if (c == '+')
		return (FLAG_PLUS);
	else if (c == ' ')
		return (FLAG_SPACE);
	else if (c == '0')
		return (FLAG_ZERO);
	else
		return (FLAG_EMPTY);
}

int						parse_flags(const char *format, unsigned char *flags)
{
	int				i;
	unsigned char	flag;

	i = 0;
	*flags = FLAG_EMPTY;
	while ((flag = ft_isflag(format[i])))
	{
		(*flags) = (*flags) | flag;
		i++;
	}
	return (i);
}
