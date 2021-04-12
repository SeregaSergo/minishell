/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:54:30 by bswag             #+#    #+#             */
/*   Updated: 2021/04/12 20:03:42 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchr_pos(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c)
	{
		if (!s[i])
			return (-1);
		i++;
	}
	return (i);
}
