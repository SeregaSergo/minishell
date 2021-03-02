/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:50:38 by bswag             #+#    #+#             */
/*   Updated: 2020/11/18 22:35:28 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*ptr_next;

	if (lst && *lst && del)
	{
		ptr = *lst;
		*lst = NULL;
		while (ptr)
		{
			if (ptr->content)
				del(ptr->content);
			ptr_next = ptr->next;
			free(ptr);
			ptr = ptr_next;
		}
	}
}
