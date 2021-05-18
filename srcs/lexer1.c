/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 18:48:35 by bswag            ###   ########.fr       */
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

void	add_to_lex_arr(t_tok ***lex, char *token_cont, int type)
{
	int		len;
	t_tok	**temp;

	len = array_size((void **)(*lex));
	temp = (t_tok **)malloc(sizeof(t_tok *) * (len + 2));
	if (!temp)
		ft_error(ER_MEMORY);
	copy_array((void **)temp, (void **)(*lex));
	if (len != 0)
		free(*lex);
	temp[len] = create_token(token_cont, type);
	temp[len + 1] = NULL;
	*lex = temp;
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
	if (check_syntax(lex))
	{
		printf("%s: syntax error\n", g_main->prompt);
		free_lex(lex);
		lex = NULL;
	}
	return (lex);
}
