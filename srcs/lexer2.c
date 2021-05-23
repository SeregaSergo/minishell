/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:13:08 by bswag             #+#    #+#             */
/*   Updated: 2021/05/23 20:01:13 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_some_symbols(char *str, int type)
{
	int		i;
	char	*stop;

	i = 0;
	if (type == TOKEN_DQOUTE)
		stop = "\"";
	if (type == TOKEN_QOUTE)
		stop = "'";
	if (type == TOKEN_GENERAL)
		stop = STOP_SYMBLS;
	while (str[i])
	{
		if (type == TOKEN_DQOUTE && str[i] == '\\' && str[i + 1] == '"')
			i += 2;
		if (ft_char_in_set(str[i], stop))
		{
			if (type != TOKEN_GENERAL)
				return (i + 1);
			else
				return (i);
		}
		if (str[i] != '\0')
			i++;
	}
	return (i);
}

int	get_token_type(char	c1, char c2)
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

void	free_token(void *t)
{
	t_tok	*tok;

	tok = (t_tok *)t;
	if (tok)
	{
		if (tok->cont)
			free(tok->cont);
		free(tok);
	}
}

int	get_next_token(char *s, int *type)
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
		return (1 + pass_some_symbols(&s[1], TOKEN_DQOUTE));
	if (*type == TOKEN_QOUTE)
		return (1 + pass_some_symbols(&s[1], TOKEN_QOUTE));
	return (0);
}
