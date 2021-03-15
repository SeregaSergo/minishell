/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bdlstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:43:38 by bswag             #+#    #+#             */
/*   Updated: 2021/03/15 22:45:38 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bdlist	*ft_bdlstnew(void *content)
{
	t_bdlist	*new_elem;

	new_elem = (t_bdlist *)malloc(sizeof(t_bdlist));
	if (new_elem != NULL)
	{
		new_elem->cont = content;
		new_elem->next = NULL;
		new_elem->prev = NULL;
	}
	return (new_elem);
}
