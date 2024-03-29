/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:09:40 by bswag             #+#    #+#             */
/*   Updated: 2021/05/25 16:44:48 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_str_envp(void)
{
	int		len;
	int		i;
	char	**envp;
	char	*tmp;

	i = 0;
	len = array_size((void **)g_main->env);
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp)
		ft_error(ER_MEMORY);
	while (i < len)
	{
		tmp = ft_strjoin(g_main->env[i]->var, "=");
		envp[i] = ft_strjoin(tmp, g_main->env[i]->cont);
		free(tmp);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	check_dir_file(char *path, char *name)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				len;

	dirp = opendir(path);
	if (dirp == NULL)
		return (1);
	len = ft_strlen(name);
	while (1)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break ;
		else if (!ft_strncmp(dp->d_name, name, len + 1))
		{
			closedir(dirp);
			return (0);
		}
	}
	closedir(dirp);
	return (1);
}

void	free_arr_char(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

char	*find_path(char *fname)
{
	char	**env;
	char	**paths;
	int		i;
	char	*path;

	env = get_val_env("PATH");
	if (env == NULL)
		return (NULL);
	paths = ft_split(*env, ':');
	i = 0;
	while (paths[i])
	{
		if (!check_dir_file(paths[i], fname))
		{
			path = ft_strjoin(paths[i], "/");
			free_arr_char(paths);
			return (path);
		}
		i++;
	}
	free_arr_char(paths);
	return (NULL);
}

int	execve_cmds(t_cmd *cmd)
{
	char	*path;
	char	*full_path;
	int		ret;
	char	**env_struct;

	if (!ft_strchr(cmd->args[0], '/'))
	{
		path = find_path(cmd->args[0]);
		if (!path)
		{
			printf("%s: No such file or directory\n", cmd->args[0]);
			return (127);
		}
		full_path = ft_strjoin(path, cmd->args[0]);
		free(path);
	}
	else
		full_path = cmd->args[0];
	env_struct = create_str_envp();
	ret = execve(full_path, cmd->args, env_struct);
	ret = 127;
	printf("%s: %s\n", full_path, strerror(errno));
	free_arr_char(env_struct);
	return (ret);
}
