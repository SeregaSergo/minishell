/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:58:22 by bswag             #+#    #+#             */
/*   Updated: 2021/05/23 20:06:34 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*create_token(char *cont, int type)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		ft_error(ER_MEMORY);
	new->cont = cont;
	new->type = type;
	return (new);
}

int	add_to_lex_arr(t_tok ***lex, char *token_cont, int type)
{
	int		len;
	t_tok	**temp;
	t_tok	*new;

	new = create_token(token_cont, type);
	if (type == TOKEN_QOUTE || type == TOKEN_DQOUTE)
	{
		if (check_closed_qouts(new, type))
			return (1);
	}
	fix_lexeme(new);
	len = array_size((void **)(*lex));
	temp = (t_tok **)malloc(sizeof(t_tok *) * (len + 2));
	if (!temp)
		ft_error(ER_MEMORY);
	copy_array((void **)temp, (void **)(*lex));
	if (len != 0)
		free(*lex);
	temp[len] = new;
	temp[len + 1] = NULL;
	*lex = temp;
	return (0);
}

int	add_to_prev_lex_arr(t_tok ***lex, char *token_cont, int type)
{
	int		len;
	t_tok	*tmp;
	char	*new;

	len = array_size((void **)(*lex));
	tmp = create_token(token_cont, type);
	if (type == TOKEN_QOUTE || type == TOKEN_DQOUTE)
	{
		if (check_closed_qouts(tmp, type))
			return (1);
	}
	fix_lexeme(tmp);
	new = ft_strjoin((*lex)[len - 1]->cont, tmp->cont);
	free(tmp->cont);
	free(tmp);
	free((*lex)[len - 1]->cont);
	(*lex)[len - 1]->cont = new;
	return (0);
}
