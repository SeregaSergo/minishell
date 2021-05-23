/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:39:24 by bswag             #+#    #+#             */
/*   Updated: 2021/05/23 19:06:09 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_env_var(char *str)
{
	t_env	**new_env;
	int		len;

	len = array_size((void **) g_main->env);
	new_env = (t_env **)malloc(sizeof(t_env *) * (len + 2));
	if (!new_env)
		ft_error(ER_MEMORY);
	copy_array((void **)new_env, (void **)g_main->env);
	new_env[len] = make_env_struct(str);
	new_env[len + 1] = NULL;
	free(g_main->env);
	g_main->env = new_env;
	return (0);
}

int	export(char *str)
{
	int	i;

	if (!str)
		return (print_env());
	i = ft_strchr_pos(str, '=');
	if (!ft_isalpha(str[0]))
	{
		printf("export: '%s' : not a valid identifier\n", str);
		return (1);
	}
	if (i < 0)
		return (1);
	if (var_exist(ft_substr(str, 0, i)))
		return (change_value_env(ft_substr(str, i + 1, ft_strlen(&str[i + 1])), \
	get_val_env(ft_substr(str, 0, i))));
	else
		return (add_new_env_var(str));
}
