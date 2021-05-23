/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/05/23 20:06:05 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_closed_qouts(t_tok *tok, int type)
{
	int	len;

	len = ft_strlen(tok->cont);
	if (len == 1)
		;
	else if (type == TOKEN_DQOUTE && tok->cont[len - 2] == '\\')
		;
	else if (tok->cont[0] == tok->cont[len - 1])
		return (0);
	free(tok->cont);
	free(tok);
	return (1);
}

int	check_redirect_file(t_tok *tok)
{
	int	type;

	if (tok == NULL)
		return (1);
	type = tok->type;
	if (type == TOKEN_GENERAL || type == TOKEN_QOUTE || type == TOKEN_DQOUTE)
		return (0);
	return (1);
}

int	check_syntax(t_tok **lex)
{
	int	i;
	int	type;

	i = 0;
	if (lex == NULL)
		return (0);
	while (lex[i])
	{
		type = lex[i]->type;
		if (i == 0 && (type == TOKEN_SEPARATOR || type == TOKEN_PIPE))
			return (1);
		else
		{
			if (type == TOKEN_IN || type == TOKEN_OUT || type == TOKEN_OUT_APP)
				if (check_redirect_file(lex[i + 1]))
					return (1);
		}
		i++;
	}
	return (0);
}	

void	free_lex(t_tok **lex)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		if (lex[i]->cont != NULL)
			free(lex[i]->cont);
		free(lex[i]);
		i++;
	}
	free(lex);
}

int	syntax_error(t_tok	***lex)
{
	printf("%s: syntax error\n", g_main->prompt);
	free_lex(*lex);
	*lex = NULL;
	return (-1);
}
