/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:41:29 by bswag             #+#    #+#             */
/*   Updated: 2021/05/16 01:29:06 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd *cmd)
{
	int	ret;

	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ret = cd(cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
	{
		set_result_prev_cmd(0);
		exit(0);
	}
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ret = ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ret = pwd();
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ret = unset(cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ret = export(cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ret = print_env();
	else
		ret = execve_cmds(cmd);
	return (ret);
}

void	make_pipes(t_cmd **cmds, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i != (n - 1))
		{
			cmds[i]->pipe_out = (int *)malloc(2 * sizeof(int));
			if (cmds[i]->pipe_out == NULL)
				ft_error(ER_MEMORY);
			if (pipe(cmds[i]->pipe_out) < 0)
				ft_error(ER_PIPE);
			pipe(cmds[i]->pipe_out);
		}
		if (i != 0)
			cmds[i]->pipe_in = cmds[i - 1]->pipe_out;
		i++;
	}
}

void	close_pipes(t_cmd **cmds, int n, int i_save)
{
	int	i;

	i = 0;
	while (i < n && n != 1)
	{
		if (i != i_save && cmds[i]->pipe_in != NULL)
			close(cmds[i]->pipe_in[0]);
		if (i != i_save && cmds[i]->pipe_out != NULL)
			close(cmds[i]->pipe_out[1]);
		if (i != (i_save + 1) && cmds[i]->pipe_in != NULL)
			close(cmds[i]->pipe_in[1]);
		if (i != (i_save - 1) && cmds[i]->pipe_out != NULL)
			close(cmds[i]->pipe_out[0]);
		i++;
	}
}

void	wait_for_all_children(int n)
{
	int	status;
	int	i;
	int	ret;

	i = 0;
	while (i < n)
	{
		ret = wait(&status);
		if (ret < 0)
			ft_error(ER_WAIT);
		i++;
	}
	set_result_prev_cmd(status);
}

void	execute_cmd_line(t_cmd_line *cmd_line)
{
	int	status;
	int	i;
	int	pid;

	i = 0;
	if (cmd_line->num_cmds > 1 || is_builtin(cmd_line->cmds[0]->args[0]))
	{
		make_pipes(cmd_line->cmds, cmd_line->num_cmds);
		while (i < cmd_line->num_cmds)
		{	
			pid = fork();
			if (pid < 0)
				ft_error(ER_FORK);
			if (pid == 0)
			{
				switch_on_signals();
				close_pipes(cmd_line->cmds, cmd_line->num_cmds, i);
				redirect_streams(cmd_line->cmds[i]);
				status = execute_cmd(cmd_line->cmds[i]);
				exit(status);
			}
			i++;
		}
		close_pipes(cmd_line->cmds, cmd_line->num_cmds, -2);
		wait_for_all_children(cmd_line->num_cmds);
	}
	else
		exec_in_the_same_proc(cmd_line->cmds[0]);
}
