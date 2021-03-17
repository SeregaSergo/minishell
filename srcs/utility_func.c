/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:28:31 by bswag             #+#    #+#             */
/*   Updated: 2021/03/18 00:01:18 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(void)
{
	int	i;
	
	i = 0;
	while (g_main->env[i])	
	{
		ft_printf("%s\n", g_main->env[i]);
		i++;
	}
}

int		array_size(void **arr)
{
	int	i;
	
	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	copy_array(void **dst, void **src)
{
	if (src)
	{
		while (*src)
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
}