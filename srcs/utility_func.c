/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:28:31 by bswag             #+#    #+#             */
/*   Updated: 2021/03/18 18:17:57 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(void)
{
	int	i;
	
	i = 0;
	while (g_main->env[i])	
	{
		ft_printf("%s=%s\n", g_main->env[i]->var, g_main->env[i]->cont);
		i++;
	}
}

/*
** Return a pointer to value of variable
*/
char	**get_val_env(char *var)
{
	int	i;

	i = 0;
	while (g_main->env[i])
	{
		if (ft_strncmp(g_main->env[i]->var, var, ft_strlen(var) + 1))
			return (&g_main->env[i]->cont);
		i++;
	}
	return (NULL);
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