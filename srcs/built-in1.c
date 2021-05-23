/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:42:22 by bswag             #+#    #+#             */
/*   Updated: 2021/05/23 18:54:46 by bswag            ###   ########.fr       */
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

void	cd_prev(char **path, char *old)
{
	char	**ptr;

	free(*path);
	ptr = get_val_env("OLDPWD");
	if (ptr == NULL)
		*path = old;
	else
		*path = ft_strdup(*ptr);
	ft_putendl_fd(*path, 1);
}

int	cd(char **path)
{
	char	*old;

	old = getcwd(NULL, 1);
	if (*path == NULL)
		return (0);
	if (!ft_strncmp(*path, "-", 2))
		cd_prev(path, old);
	if (!chdir(*path))
	{
		change_value_env(old, get_val_env("OLDPWD"));
		change_value_env(getcwd(NULL, 1), get_val_env("PWD"));
		return (0);
	}
	if (old != NULL)
		free(old);
	ft_putstr_fd("cd: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
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
