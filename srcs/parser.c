/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:58:34 by bswag             #+#    #+#             */
/*   Updated: 2021/03/19 19:24:31 by bswag            ###   ########.fr       */
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
		if (lex[i]->type != TOKEN_PIPE)
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

void		fill_lexemes_struct(t_cmd *cmd, t_tok **lex)
{
	
}

t_cmd		*create_comand(t_tok **lex, int *i)
{
	int		len;
	t_cmd	*cmd;
	
	len = 1;
	while (lex[*i] && lex[*i]->type != TOKEN_SEPARATOR && lex[*i]->type != TOKEN_PIPE)
		len++;
	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		ft_error(ER_MEMORY);
	cmd->num_args = len;
	if (!(cmd->args =(char **)malloc(sizeof(char *) * (len + 1))))
		ft_error(ER_MEMORY);
	cmd->args[len] = NULL;
	fill_cmd_with_args(cmd, &lex[*i]);
	*i += len;
}

void		cut_lexemes_struct(t_tok ***lex, int i)
{
	int	len;

	len = (**lex == NULL) ? 
}

t_cmd_line	*parse_input(t_tok ***lex)
{
	t_cmd_line	*line;
	// t_cmd		*cmd;
	int			i_lex;
	int			n_cmd;
	
	i_lex = 0;
	n_cmd = 0;
	line = NULL;
	line = init_cmd_line(*lex);
	while (n_cmd < line->num_cmds)
	{
		line->cmds[n_cmd] = create_comand((*lex), &i_lex);
		n_cmd++;
	}
	cut_lexemes_struct(lex, i_lex);
	return (line);
}