/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:17:37 by bswag             #+#    #+#             */
/*   Updated: 2021/02/02 19:18:21 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_content(char *str, char *pattern)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(ft_char_in_set(str[i], pattern)))
			return (0);
		i++;
	}
	return (1);
}