/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:19:10 by bswag             #+#    #+#             */
/*   Updated: 2020/12/23 20:40:47 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	parse_type(const char *format, char *type)
{
	int	i;

	i = 0;
	*type = '\0';
	if (ft_strchr_null("cspdiuxX%", *format))
	{
		*type = *format;
		i++;
	}
	return (i);
}
