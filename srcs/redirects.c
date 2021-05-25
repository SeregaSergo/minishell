/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 01:24:39 by bswag             #+#    #+#             */
/*   Updated: 2021/05/25 16:42:37 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file, int type)
{
	int	fd;

	if (type == TOKEN_IN)
		fd = open(file, O_RDONLY);
	else if (type == TOKEN_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

int	file_redirect(t_list *files, int stream)
{
	int		fd;
	t_list	*ptr;
	t_tok	*tok_ptr;

	ptr = files;
	while (ptr != NULL)
	{
		tok_ptr = ((t_tok *)ptr->content);
		fd = open_file(tok_ptr->cont, tok_ptr->type);
		if (fd < 0)
		{
			printf("%s: %s\n", tok_ptr->cont, strerror(errno));
			return (1);
		}
		if (ptr->next != NULL)
			close(fd);
		ptr = ptr->next;
	}
	dup2(fd, stream);
	close(fd);
	return (0);
}

int	redirect_streams(t_cmd *cmd)
{
	if (cmd->redir_in == NULL)
	{
		if (cmd->pipe_in != NULL)
			dup2(cmd->pipe_in[0], 0);
	}
	else if (file_redirect(cmd->redir_in, 0))
		return (1);
	if (cmd->redir_out == NULL)
	{
		if (cmd->pipe_out != NULL)
			dup2(cmd->pipe_out[1], 1);
	}
	else if (file_redirect(cmd->redir_out, 1))
		return (1);
	if (cmd->pipe_in != NULL)
		close(cmd->pipe_in[0]);
	if (cmd->pipe_out != NULL)
		close(cmd->pipe_out[1]);
	return (0);
}
