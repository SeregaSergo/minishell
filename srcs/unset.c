/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:54:31 by egilbert          #+#    #+#             */
/*   Updated: 2021/04/12 20:24:10 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strcmp(char *s1, char*s2)
{
	int i;

	i = -1;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[++i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (0);
}

void	free_env(t_env *fr)
{
	free(fr->cont);
	free(fr->var);
	free(fr);
}

void	clone_without_one(int skip, int len)
{
	t_env	**new;
	int		i;
	t_env	**chp_new;

	if (!(new = (t_env **)malloc(len * sizeof(t_env *))))
		ft_error(ER_MEMORY);
	i = -1;
	chp_new = new;
	while (g_main->env[++i])
	{
		if (i != skip)
		{
			*new = g_main->env[i];
			new++;
		}
		else
			free_env(g_main->env[i]);
	}
	*new = NULL;
	free(g_main->env);
	g_main->env = chp_new;
}

int		var_exist(char *var)
{
	int i;

	i = -1;
	while (g_main->env[++i] != NULL)
		if (!ft_strcmp(g_main->env[i]->var, var))
			return(1);
	free(var);
	return (0);
}

void	unset(char *var)
{
	int i;

	i = -1;
	while (g_main->env[++i])
	{
		if (!ft_strcmp(g_main->env[i]->var, var))
		{
			clone_without_one(i, array_size((void **)g_main->env));
			break;
		}
	}
}
