/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bdlstfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:03:41 by bswag             #+#    #+#             */
/*   Updated: 2021/03/16 16:01:50 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Looking for elem number (pos), or last if there is no such
*/

t_bdlist	*ft_bdlstfind(t_bdlist *list, int pos)
{
	int	i;

	i = 0;
	while (i <= pos && list && list->next)
	{
		list = list->next;
		i++;
	}
	return (list);
}
