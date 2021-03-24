/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:26:22 by bswag             #+#    #+#             */
/*   Updated: 2021/03/24 14:55:34 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    trim_qoutes(char **cont)
{
	char    *tmp;

	if (!(tmp = ft_substr(*cont, 1, ft_strlen(*cont) - 2)))
		ft_error(ER_MEMORY);
	free(*cont);
	*cont = tmp;
}

void	cut_backslash(char **cont)
{
	int	i;

	i = 0;
	while ((*cont)[i])
	{
		if ((*cont)[i] == '\\')
			*cont = delete_str_pos(i, 1, *cont);
		i++;
	}
}

void	replace_env_vars(char **cont)
{
	int		i;
	int		n;
	char	*var;
	char	**val;
	
	i = 0;
	while ((*cont)[i])
	{
		if ((*cont)[i] == '$')
		{
			n = i + 1;
			if ((*cont)[n] == '?')
				n++;
			else
				while (ft_isalnum((*cont)[n]))
					n++;
			var = ft_substr(*cont, i + 1 , n - i - 1);
			val = get_val_env(var);
			free(var);
			*cont = delete_str_pos(i, n - i, *cont);
			if (val != NULL)
			{
				*cont = paste_str_pos(i, *cont, *val);
				i += ft_strlen(*val) - 1;
			}
		}
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
		cut_backslash(&lex->cont);
		replace_env_vars(&lex->cont);
		replace_home_dir(&lex->cont);
	}
	else if (lex->type == TOKEN_QOUTE)
		trim_qoutes(&lex->cont);
	else if (lex->type == TOKEN_DQOUTE)
	{
		trim_qoutes(&lex->cont);
		cut_backslash(&lex->cont);
		replace_env_vars(&lex->cont);
	}
}