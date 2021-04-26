/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:33:16 by egilbert          #+#    #+#             */
/*   Updated: 2021/04/25 20:31:28 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_env_value(char **old, char *new)
{
	free(*old);
	*old = ft_strdup(new);
}

void	execve_cmds(t_cmd_line	*cmd)
{
	while 
}

void	execute_cmd_line(t_cmd_line	*cmd)
{
	if(!ft_strncmp(cmd->cmds[0]->args[0], "cd", 2))
		cd(cmd->cmds[0]->args[1]);
	else if(!ft_strncmp(cmd->cmds[0]->args[0], "exit", 4))
		exit(0);
	else if(!ft_strncmp(cmd->cmds[0]->args[0], "echo", 4))
		ft_echo(cmd->cmds[0]->args);
	else if(!ft_strncmp(cmd->cmds[0]->args[0], "pwd", 3))
		pwd();
	else if (!ft_strcmp(cmd->cmds[0]->args[0], "unset"))
		unset(cmd->cmds[0]->args[1]);
	else if (!ft_strcmp(cmd->cmds[0]->args[0], "export"))
		export(cmd->cmds[0]->args[1]);
	else if (!ft_strcmp(cmd->cmds[0]->args[0], "env"))
		print_env(0);
	else
		execve_cmds();

}

void	cd(char *path)
{
	char *old;

	old = getcwd(NULL, 1);
	if (!chdir(path))
	{
		change_env_value(get_val_env("OLDPWD"), old);
		change_env_value(get_val_env("PWD"), getcwd(NULL, 1));
		free(old);
		print_env(0);
		return ;
	}
	free(old);
	perror("cd");
}
