/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:07:31 by bswag             #+#    #+#             */
/*   Updated: 2021/05/01 20:37:17 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	**last;
	t_list	*elem;
	void	*new_cont;

	new_lst = NULL;
	last = &new_lst;
	while (lst)
	{
		new_cont = f(lst->content);
		elem = ft_lstnew(new_cont);
		if (elem)
		{
			ft_lstadd_back(last, elem);
			last = &(elem->next);
			lst = lst->next;
		}
		else
		{
			del(new_cont);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
	}
	return (new_lst);
}
