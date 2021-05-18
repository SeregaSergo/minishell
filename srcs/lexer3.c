/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 18:31:05 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_closed_qouts(char *cont)
{
	int	len;

	len = ft_strlen(cont);
	if (cont[0] == cont[len - 1])
		return (0);
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
			if (type == TOKEN_DQOUTE || type == TOKEN_QOUTE)
				if (check_closed_qouts(lex[i]->cont))
					return (1);
		}
		i++;
	}
	return (0);
}	
