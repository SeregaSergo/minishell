/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/03/18 00:20:53 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pass_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}
	
int		pass_some_symbols(char *str, int type)
{
	int		i;
	char	*stop;
	int		len;
	
	i = 0;
	len = ft_strlen(str);
	if (type == TOKEN_DQOUTE)
		stop = "\"";
	if (type == TOKEN_QOUTE)
		stop = "'";
	if (type == TOKEN_GENERAL)
		stop = STOP_SYMBLS;
	while (i < len && !ft_char_in_set(str[i], stop))
	{
		i++;
		if (str[i] == '\\' && type != TOKEN_QOUTE)
			i += 2;
	}
	(i >= len && (type != TOKEN_GENERAL)) ? i-- : 0;
	return (i);
}

int		get_token_type(char	c1, char c2)
{
	if (c1 == '|')
		return (TOKEN_PIPE);
	else if (c1 == ';')
		return (TOKEN_SEPARATOR);
	else if (c1 == '<')
		return (TOKEN_IN);
	else if (c1 == '>' && c2 == '>')
		return (TOKEN_OUT_APP);
	else if (c1 == '>')
		return (TOKEN_OUT);
	else if (c1 == '"')
		return (TOKEN_DQOUTE);
	else if (c1 == '\'')
		return (TOKEN_QOUTE);
	else
		return (TOKEN_GENERAL);
}

int		get_next_token(char *s, int *type)
{
	*type = get_token_type(s[0], s[1]);
	if (*type == TOKEN_OUT || *type == TOKEN_PIPE || \
		*type == TOKEN_SEPARATOR || *type == TOKEN_IN)
		return (1);
	if (*type == TOKEN_OUT_APP)
		return (2);
	if (*type == TOKEN_GENERAL)
		return (1 + pass_some_symbols(&s[1], TOKEN_GENERAL));
	if (*type == TOKEN_DQOUTE)
		return (2 + pass_some_symbols(&s[1], TOKEN_DQOUTE));
	if (*type == TOKEN_QOUTE)
		return (2 + pass_some_symbols(&s[1], TOKEN_QOUTE));
	return (0);
}

void	free_token(t_tok *tok)
{
	if (tok)
	{
		if (tok->cont)
			free(tok->cont);
		free(tok);
	}
}

t_tok	*create_token(char *cont, int type)
{
	t_tok	*new;
	
	if (!(new = (t_tok *)malloc(sizeof(t_tok))))
		ft_error(ER_MEMORY);
	new->cont = cont;
	new->type = type;
	return (new);
}

void	add_to_lex_arr(t_tok ***lex, char *token_cont, int type)
{
	int		len;
	t_tok	**temp;
	
	len = array_size((void **)(*lex));
	if (!(temp = (t_tok **)malloc(sizeof(t_tok *) * (len + 2))))
		ft_error(ER_MEMORY);
	copy_array((void **)temp, (void **)(*lex));
	if (len != 0)
		free(*lex);
	temp[len] = create_token(token_cont, type);
	temp[len + 1] = NULL;
	*lex = temp;
}

t_tok	**tokenize_input(char *s)
{
	t_tok	**lex;
	int		i;
	int		len;
	int		type;

	i = 0;
	lex = NULL;
	while (s[i])
	{
		i += pass_white_spaces(&s[i]);
		len = get_next_token(&s[i], &type);
		add_to_lex_arr(&lex, ft_substr(s, i, len), type);
		i += len;
		i += pass_white_spaces(&s[i]);
	}
	return (lex);
}