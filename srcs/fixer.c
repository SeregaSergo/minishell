/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:26:22 by bswag             #+#    #+#             */
/*   Updated: 2021/03/18 19:43:05 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    trim_qoutes(char **cont, char c)
{
	char    *tmp;

	if ((*cont)[ft_strlen(*cont) - 1] != c)
		ft_error(ER_SINGLE_QOUTE);
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
			*cont = delete_char_pos(i, *cont);
		i++;
	}
}

void	replace_env_vars(char **cont)
{
	int		i;
	int		n;
	char	*var;
	char	*val;
	
	i = 0;
	while (*cont[i])
	{
		if (*cont[i] == '$')
		{
			n = i + 1;
			while (ft_isalnum(*cont[n]))
				n++;
			var = ft_substr(*cont, i + 1 , n - i - 1);
			*cont = delete_str_pos(i, n - i, *cont);
			val = *get_val_env(var);
			*cont = paste_str_pos(i, *cont, val);
			free(var);
			i +=ft_strlen(val);
		}
		i++;
	}
}

void	fix_lexemes(t_tok **lex)
{
	int	i;

	i = 0;
	while (lex[i])
	{
		// if (lex[i]->type == TOKEN_GENERAL)
		// {
		// }
		if (lex[i]->type == TOKEN_QOUTE)
			trim_qoutes(&lex[i]->cont, '\'');
		else if (lex[i]->type == TOKEN_DQOUTE)
		{
			trim_qoutes(&lex[i]->cont, '"');
			cut_backslash(&lex[i]->cont);
			replace_env_vars(&lex[i]->cont);
		}
		i++;
	}
}