/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:41:29 by bswag             #+#    #+#             */
/*   Updated: 2021/05/25 16:35:55 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cycle_execute_cmd(char **args, int (*func)(char *))
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (*args == NULL)
		ret = func(args[0]);
	while (args[++i])
		ret = func(args[i]);
	return (ret);
}

int	execute_cmd(t_cmd *cmd)
{
	int	ret;

	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ret = cd(&cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ret = exit_cmd(&cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ret = ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ret = pwd();
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ret = cycle_execute_cmd(&cmd->args[1], unset);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ret = cycle_execute_cmd(&cmd->args[1], export);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ret = print_env();
	else
		ret = execve_cmds(cmd);
	return (ret);
}

void	wait_for_all_children(int n)
{
	int	stat;
	int	i;
	int	ret;

	i = -1;
	while (++i < n)
	{
		ret = wait(&stat);
		if (ret < 0)
			ft_error(ER_WAIT);
		if (WIFSIGNALED(stat))
		{
			if (stat == SIGINT)
				printf("\n");
			if (stat == SIGKILL || stat == SIGTERM)
				printf("Kill: %i\n", stat);
			if (stat == SIGTERM)
				printf("Terminate:  %i\n", stat);
			if (stat == SIGQUIT)
				printf("Quit: %i\n", stat);
			set_result_prev_cmd(stat + 128);
		}
		else
			set_result_prev_cmd(WEXITSTATUS(stat));
	}
}

void	exec_fork_main(t_cmd **cmds, int num_cmds, int index)
{
	int	status;

	switch_on_signals();
	close_pipes(cmds, num_cmds, index);
	if (redirect_streams(cmds[index]))
		exit(1);
	status = execute_cmd(cmds[index]);
	exit(status);
}

void	execute_cmd_line(t_cmd_line *cmd_line)
{
	int	i;
	int	pid;

	i = 0;
	if (cmd_line->num_cmds > 1 || is_builtin(cmd_line->cmds[0]->args[0]))
	{
		make_pipes(cmd_line->cmds, cmd_line->num_cmds);
		signal(SIGINT, sig_handler);
		while (i < cmd_line->num_cmds)
		{	
			pid = fork();
			if (pid < 0)
				ft_error(ER_FORK);
			if (pid == 0)
				exec_fork_main(cmd_line->cmds, cmd_line->num_cmds, i);
			i++;
		}
		close_pipes(cmd_line->cmds, cmd_line->num_cmds, -2);
		wait_for_all_children(cmd_line->num_cmds);
	}
	else
		exec_in_the_same_proc(cmd_line->cmds[0]);
}
