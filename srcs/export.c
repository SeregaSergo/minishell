/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:45:02 by egilbert          #+#    #+#             */
/*   Updated: 2021/04/12 21:57:09 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_value_env(char *new, char **value)
{
	if (!ft_strcmp(*value, new))
		return ;
	free(*value);
	*value = new;
}

void	export(char *str)
{
	t_env	**new_env;
	int		len;
	int		i;

	if (!str)
		return (print_env(1));
	len = array_size((void **) g_main->env);
	if (!(new_env = (t_env **)malloc(sizeof(t_env *) * (len + 2))))
		ft_error(ER_MEMORY);
	if ((i = ft_strchr_pos(str, '=')) < 0)
		return ;
	if (var_exist(ft_substr(str, 0, i)))
		return (change_value_env(ft_substr(str, i + 1,ft_strlen(&str[i + 1])),
			get_val_env(ft_substr(str, 0, i))));
	i = -1;
	while (g_main->env[++i])
		new_env[i] = g_main->env[i];
	new_env[i] = make_env_struct(str);
	new_env[++i] = NULL;
	free(g_main->env);
	g_main->env = new_env;
}
