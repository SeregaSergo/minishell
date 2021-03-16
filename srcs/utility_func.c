/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:28:31 by bswag             #+#    #+#             */
/*   Updated: 2021/03/16 22:22:38 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(char **envp)
{
	int	i;
	
	i = 0;
	if (envp != NULL)
	{
		while (envp[i])	
		{
			ft_printf("%s\n", envp[i]);
			i++;
		}
	}
}

int		array_size(char **arr)
{
	int	i;
	
	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	copy_array(char **dst, char **src)
{
	while (src)
	{
		dst = src;
		dst++;
		src++;
	}
}