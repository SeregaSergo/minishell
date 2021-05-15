/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:41:29 by bswag             #+#    #+#             */
/*   Updated: 2021/05/15 20:53:43 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_cmd *cmd)
{
	int	ret;

	if(!ft_strncmp(cmd->args[0], "cd", 2))
		ret = cd(cmd->args[1]);
	else if(!ft_strncmp(cmd->args[0], "exit", 4))
		exit(0);
	else if(!ft_strncmp(cmd->args[0], "echo", 4))
		ret = ft_echo(cmd->args);
	else if(!ft_strncmp(cmd->args[0], "pwd", 3))
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
		if (cmds[i]->redir_in != NULL)
		{
			if (i != i_save)
				close(cmds[i]->pipe_in[0]);
			close(cmds[i]->pipe_in[1]);
		}
		if (cmds[i]->redir_out != NULL)
		{
			if (i != i_save)
				close(cmds[i]->pipe_out[1]);
			close(cmds[i]->pipe_out[0]);
		}
		i++;
	}
}

void	file_redirect(t_list *files, int stream)
{
	int		fd;
	t_list	*ptr;
	t_tok	*tok_ptr;

	ptr = files;
	while (ptr != NULL)
	{
		tok_ptr = ((t_tok *)files->content);
		if (tok_ptr->type == TOKEN_IN)
			fd = open(tok_ptr->cont, O_RDONLY);
		else if (tok_ptr->type == TOKEN_OUT)
			fd = open(tok_ptr->cont, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		else
			fd = open(tok_ptr->cont, O_WRONLY|O_APPEND|O_CREAT, 0644);
		if (ptr->next != NULL)
			close(fd);
		ptr = ptr->next;
	}
	dup2(fd, stream);
	close(fd);
}

void	redirect_streams(t_cmd *cmd)
{
	if (cmd->redir_in == NULL) // если входных редиректов нет
	{
		if (cmd->pipe_in != NULL) // если есть входной пайп
			dup2(cmd->pipe_in[0], 0);
	}
	else		// есть входные редиректы
		file_redirect(cmd->redir_in, 0);
	if (cmd->redir_out == NULL) // если выходных редиректов нет
	{
		if (cmd->pipe_out != NULL) // если есть выходной пайп
			dup2(cmd->pipe_out[1], 1);
	}
	else		// есть выходные редиректы
		file_redirect(cmd->redir_out, 1);
	if (cmd->pipe_in != NULL)
		close(cmd->pipe_in[0]);
	if (cmd->pipe_out != NULL)
		close(cmd->pipe_out[1]);
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

void	execute_cmd_line(t_cmd_line * cmd_line)
{
	int	status;
	int	i;
	int	pid;

	i = 0;
	if (cmd_line->num_cmds > 1)
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
		close_pipes(cmd_line->cmds, cmd_line->num_cmds, -1);
		wait_for_all_children(cmd_line->num_cmds);
	}
	else
		set_result_prev_cmd(execute_cmd(cmd_line->cmds[0]));
}