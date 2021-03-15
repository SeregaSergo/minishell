/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bdlstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:11:39 by bswag             #+#    #+#             */
/*   Updated: 2021/03/15 22:46:04 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bdlstadd_front(t_bdlist **lst, t_bdlist *new)
{
	if (lst && new)
	{
		(*lst)->prev = new;
		new->next = *lst;
		*lst = new;
	}
}
