/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:58:34 by bswag             #+#    #+#             */
/*   Updated: 2021/05/24 18:40:11 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_redir_elem(int type, char *cont)
{
	t_list	*new;
	t_tok	*tok;

	tok = (t_tok *)malloc(sizeof(t_tok));
	if (!tok)
		ft_error(ER_MEMORY);
	tok->type = type;
	tok->cont = ft_strdup(cont);
	if (!(tok->cont))
		ft_error(ER_MEMORY);
	new = ft_lstnew(tok);
	if (!new)
		ft_error(ER_MEMORY);
	return (new);
}

char	**add_argument(char **args, char *cont)
{
	int		len;
	char	**new;

	len = array_size((void **)args);
	new = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new)
		ft_error(ER_MEMORY);
	copy_array((void **)new, (void **)args);
	new[len] = ft_strdup(cont);
	if (!new[len])
		ft_error(ER_MEMORY);
	new[len + 1] = NULL;
	free(args);
	return (new);
}

t_cmd	*init_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		ft_error(ER_MEMORY);
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->pipe_in = NULL;
	cmd->pipe_out = NULL;
	cmd->args = args;
	cmd->num_args = 0;
	return (cmd);
}

void	update_redir_struct(t_tok **lex, int *i, int type, t_cmd *cmd)
{
	(*i)++;
	fix_lexeme(lex[*i]);
	if (type == TOKEN_IN)
		ft_lstadd_back(&cmd->redir_in, create_redir_elem(TOKEN_IN, \
		lex[*i]->cont));
	else
		ft_lstadd_back(&cmd->redir_out, create_redir_elem(lex[*i - 1]->type, \
			lex[*i]->cont));
}

t_cmd	*create_comand(t_tok **lex, int *i)
{
	t_cmd	*cmd;
	int		type;

	cmd = init_cmd(NULL);
	if (lex[*i])
		type = lex[*i]->type;
	while (lex[*i] && type != TOKEN_SEPARATOR && type != TOKEN_PIPE)
	{
		if (type == TOKEN_IN || type == TOKEN_OUT || type == TOKEN_OUT_APP)
			update_redir_struct(lex, i, type, cmd);
		else
		{
			cmd->args = add_argument(cmd->args, lex[*i]->cont);
			cmd->num_args++;
		}
		(*i)++;
		if (lex[*i])
			type = lex[*i]->type;
	}
	return (cmd);
}
