/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 01:24:39 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 17:19:27 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_redirect(t_list *files, int stream)
{
	int		fd;
	t_list	*ptr;
	t_tok	*tok_ptr;

	ptr = files;
	while (ptr != NULL)
	{
		tok_ptr = ((t_tok *)ptr->content);
		if (tok_ptr->type == TOKEN_IN)
			fd = open(tok_ptr->cont, O_RDONLY);
		else if (tok_ptr->type == TOKEN_OUT)
			fd = open(tok_ptr->cont, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(tok_ptr->cont, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (ptr->next != NULL)
			close(fd);
		ptr = ptr->next;
	}
	dup2(fd, stream);
	close(fd);
}

void	redirect_streams(t_cmd *cmd)
{
	if (cmd->redir_in == NULL)
	{
		if (cmd->pipe_in != NULL)
			dup2(cmd->pipe_in[0], 0);
	}
	else
		file_redirect(cmd->redir_in, 0);
	if (cmd->redir_out == NULL)
	{
		if (cmd->pipe_out != NULL)
			dup2(cmd->pipe_out[1], 1);
	}
	else
		file_redirect(cmd->redir_out, 1);
	if (cmd->pipe_in != NULL)
		close(cmd->pipe_in[0]);
	if (cmd->pipe_out != NULL)
		close(cmd->pipe_out[1]);
}
