/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:42:22 by bswag             #+#    #+#             */
/*   Updated: 2021/05/16 01:21:09 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (i == 1 && !ft_strncmp(args[1], "-n", 2) && args[1][2] == 0)
			i++;
		if (args[i] != NULL)
			ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			write(1, " ", 1);
	}
	if (args[1] && !ft_strncmp(args[1], "-n", 2) && args[1][2] == 0)
		;
	else
		write(1, "\n", 1);
	return (0);
}

void	change_env_value(char **old, char *new)
{
	free(*old);
	*old = ft_strdup(new);
}

int	cd(char *path)
{
	char	*old;

	old = getcwd(NULL, 1);
	if (!chdir(path))
	{
		change_env_value(get_val_env("OLDPWD"), old);
		change_env_value(get_val_env("PWD"), getcwd(NULL, 1));
		free(old);
		return (0);
	}
	free(old);
	ft_putstr_fd("cd: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	export(char *str)
{
	t_env	**new_env;
	int		len;
	int		i;

	if (!str)
		return (print_env());
	len = array_size((void **) g_main->env);
	new_env = (t_env **)malloc(sizeof(t_env *) * (len + 2));
	if (!new_env)
		ft_error(ER_MEMORY);
	i = ft_strchr_pos(str, '=');
	if (i < 0)
		return (0);
	if (var_exist(ft_substr(str, 0, i)))
		return (change_value_env(ft_substr(str, i + 1, ft_strlen(&str[i + 1])), \
	get_val_env(ft_substr(str, 0, i))));
	i = -1;
	while (g_main->env[++i])
		new_env[i] = g_main->env[i];
	new_env[i] = make_env_struct(str);
	new_env[++i] = NULL;
	free(g_main->env);
	g_main->env = new_env;
	return (0);
}

int	pwd(void)
{
	char	*line;

	line = getcwd(NULL, 1);
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
	free(line);
	return (0);
}
