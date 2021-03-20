/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:58:34 by bswag             #+#    #+#             */
/*   Updated: 2021/03/20 17:50:37 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_line	*init_cmd_line(t_tok **lex)
{
	int			i;
	int			len;
	t_cmd_line	*cmd_line;
	
	i = 0;
	len = 1;
	while (lex[i] && lex[i]->type != TOKEN_SEPARATOR)
	{
		if (lex[i]->type == TOKEN_PIPE)
			len++;
		i++;
	}
	if (!(cmd_line = (t_cmd_line *)malloc(sizeof(t_cmd_line))))
		ft_error(ER_MEMORY);
	cmd_line->num_cmds = len;
	if (!(cmd_line->cmds =(t_cmd **)malloc(sizeof(t_cmd *) * (len + 1))))
		ft_error(ER_MEMORY);
	cmd_line->cmds[len] = NULL;
	return (cmd_line);
}

t_list		*create_redir_elem(int type, char *cont)
{
	t_list	*new;
	t_tok	*tok;
	
	if (!(tok = (t_tok *)malloc(sizeof(t_tok))))
		ft_error(ER_MEMORY);
	tok->type = type;
	if (!(tok->cont = ft_strdup(cont)))
		ft_error(ER_MEMORY);
	if (!(new = ft_lstnew(tok)))
		ft_error(ER_MEMORY);
	return (new);
}

char		**add_argument(char **args, char *cont)
{
	int		len;
	char	**new;
	
	len = array_size((void **)args);
	if (!(new = (char **)malloc(sizeof(char *) * (len + 2))))
		ft_error(ER_MEMORY);
	copy_array((void **)new, (void **)args);
	if (!(new[len] = ft_strdup(cont)))
		ft_error(ER_MEMORY);
	new[len + 1] = NULL;
	return (new);
}

t_cmd		*init_cmd(char **args)
{
	t_cmd	*cmd;
	
	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		ft_error(ER_MEMORY);
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->args = args;
	cmd->num_args = 0;
	return (cmd);
}

t_cmd		*create_comand(t_tok **lex, int *i)
{
	t_cmd	*cmd;
	
	cmd = init_cmd(NULL);
	while (lex[*i] && lex[*i]->type != TOKEN_SEPARATOR && lex[*i]->type != TOKEN_PIPE)
	{
		if (lex[*i]->type == TOKEN_IN)
		{
			(*i)++;
			fix_lexeme(lex[*i]);
			ft_lstadd_back(&cmd->redir_in, create_redir_elem(TOKEN_IN, lex[*i]->cont));
		}
		else if (lex[*i]->type == TOKEN_OUT || lex[*i]->type == TOKEN_OUT_APP)
		{
			(*i)++;
			fix_lexeme(lex[*i]);
			ft_lstadd_back(&cmd->redir_out, create_redir_elem(lex[*i - 1]->type, lex[*i]->cont));
		}
		else
		{
			fix_lexeme(lex[*i]);
			cmd->args = add_argument(cmd->args, lex[*i]->cont);
			cmd->num_args++;
		}
		(*i)++;
	}
	return (cmd);
}

t_tok	**cut_lexemes_struct(t_tok **lex, int pos)
{
	int		i;
	int		len;
	t_tok	**new;
	
	i = 0;
	len = array_size((void **)lex);
	while (i < pos)
	{
		free(lex[i]->cont);
		free(lex[i]);
		i++;
	}
	if (len != pos)
	{
		if (!(new = (t_tok **)malloc(sizeof(t_tok *) * (len - pos + 1))))
			ft_error(ER_MEMORY);
		copy_array((void **)new, (void **)&lex[pos]);
		new[len - pos] = NULL;
	}
	else
		new = NULL;
	free(lex);
	return (new);
}

t_cmd_line	*parse_input(t_tok ***lex)
{
	t_cmd_line	*line;
	int			i_lex;
	int			n_cmd;
	
	i_lex = 0;
	n_cmd = 0;
	line = init_cmd_line(*lex);
	while (n_cmd < line->num_cmds)
	{
		line->cmds[n_cmd] = create_comand((*lex), &i_lex);
		i_lex += ((*lex)[i_lex]) ? 1 : 0;
		n_cmd++;
	}
	*lex = cut_lexemes_struct(*lex, i_lex);
	return (line);
}