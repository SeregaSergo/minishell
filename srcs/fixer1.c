/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:26:22 by bswag             #+#    #+#             */
/*   Updated: 2021/05/23 15:36:03 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_qoutes(char **cont)
{
	char	*tmp;

	tmp = ft_substr(*cont, 1, ft_strlen(*cont) - 2);
	if (!tmp)
		ft_error(ER_MEMORY);
	free(*cont);
	*cont = tmp;
}

void	cut_backslash(char **cont, int type)
{
	int	i;

	i = 0;
	while ((*cont)[i])
	{
		if ((*cont)[i] == '\\' && type == TOKEN_GENERAL)
			*cont = delete_str_pos(i, 1, *cont);
		if ((*cont)[i] == '\\' && type == TOKEN_DQOUTE && (*cont)[i + 1] == '"')
			*cont = delete_str_pos(i, 1, *cont);
		i++;
	}
}

void	replace_home_dir(char **cont)
{
	int		i;
	char	**val;

	i = 0;
	while ((*cont)[i])
	{
		if ((*cont)[i] == '~')
		{
			val = get_val_env("HOME");
			if (val != NULL)
			{
				*cont = delete_str_pos(i, 1, *cont);
				*cont = paste_str_pos(i, *cont, *val);
				i += ft_strlen(*val) - 1;
			}
		}
		i++;
	}
}

void	fix_lexeme(t_tok *lex)
{
	if (lex->type == TOKEN_GENERAL)
	{
		replace_env_vars(&lex->cont);
		cut_backslash(&lex->cont, lex->type);
		replace_home_dir(&lex->cont);
	}
	else if (lex->type == TOKEN_QOUTE)
		trim_qoutes(&lex->cont);
	else if (lex->type == TOKEN_DQOUTE)
	{
		trim_qoutes(&lex->cont);
		replace_env_vars(&lex->cont);
		cut_backslash(&lex->cont, lex->type);
	}
}
