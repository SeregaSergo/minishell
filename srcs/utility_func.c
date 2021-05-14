/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:28:31 by bswag             #+#    #+#             */
/*   Updated: 2021/05/13 00:04:12 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(void)
{
	int	i;
	
	i = 0;
	while (g_main->env[i])	
	{
		ft_printf("%s=%s\n", g_main->env[i]->var, g_main->env[i]->cont);
		i++;
	}
	return (0);
}

/*
** Use this function when comand has completed the execution to set
** a result. This is necessary for $?.
*/
void	set_result_prev_cmd(int	res)
{
	g_main->i_result_prev_cmd = res;
	if (g_main->c_result_prev_cmd != NULL)
		free(g_main->c_result_prev_cmd);
	g_main->c_result_prev_cmd = ft_itoa(res);
}

/*
** Return a pointer(!!!) to value of variable, so you can change it or print.
*/
char	**get_val_env(char *var)
{
	int	i;

	i = 0;
	if (!ft_strncmp(var, "?", 1))
		return (&g_main->c_result_prev_cmd);
	while (g_main->env[i])
	{
		if (!ft_strncmp(g_main->env[i]->var, var, ft_strlen(var) + 1))
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

/*
** It does not make a deep copy, just make lightweight copy of pointers.
*/
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