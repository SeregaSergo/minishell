/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/05/23 20:04:05 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void	cut_line_string(char **s, int i)
{
	char	*tmp;

	tmp = NULL;
	if ((*s)[i] == ';')
		tmp = ft_strdup(&((*s)[i + 1]));
	free(*s);
	*s = tmp;
}

int	merge_or_create(int len, int type)
{
	if (len == 0 && \
	(type == TOKEN_GENERAL || type == TOKEN_QOUTE || type == TOKEN_DQOUTE))
		return (1);
	else
		return (0);
}

int	make_lexem_structure(char **s, t_tok ***lex)
{
	int		i;
	int		len;
	int		type;
	int		mode;
	int		ret;

	i = 0;
	mode = 0;
	i += pass_white_spaces(&((*s)[i]));
	while ((*s)[i] && (*s)[i] != ';')
	{
		len = get_next_token(&((*s)[i]), &type);
		if (mode == 0)
			ret = add_to_lex_arr(lex, ft_substr(*s, i, len), type);
		else
			ret = add_to_prev_lex_arr(lex, ft_substr(*s, i, len), type);
		if (ret)
			return (syntax_error(lex));
		i += len;
		len = pass_white_spaces(&((*s)[i]));
		mode = merge_or_create(len, type);
		i += len;
	}
	return (i);
}

t_tok	**tokenize_input(char **s)
{
	t_tok	**lex;
	int		i;

	lex = NULL;
	i = make_lexem_structure(s, &lex);
	if (i == -1)
	{
		free(*s);
		*s = NULL;
	}
	else
	{
		cut_line_string(s, i);
		if (check_syntax(lex))
			syntax_error(&lex);
	}
	return (lex);
}
