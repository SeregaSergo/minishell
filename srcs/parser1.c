/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 18:21:38 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 18:26:18 by bswag            ###   ########.fr       */
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
	cmd_line = (t_cmd_line *)malloc(sizeof(t_cmd_line));
	if (!cmd_line)
		ft_error(ER_MEMORY);
	cmd_line->num_cmds = len;
	cmd_line->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (len + 1));
	if (!cmd_line->cmds)
		ft_error(ER_MEMORY);
	cmd_line->cmds[len] = NULL;
	return (cmd_line);
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
		new = (t_tok **)malloc(sizeof(t_tok *) * (len - pos + 1));
		if (!new)
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
		if ((*lex)[i_lex])
			i_lex++;
		n_cmd++;
	}
	*lex = cut_lexemes_struct(*lex, i_lex);
	return (line);
}
