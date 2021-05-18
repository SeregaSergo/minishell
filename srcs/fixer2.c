/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:26:22 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 17:39:40 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_val_env_free(char *var)
{
	char	**val;

	val = get_val_env(var);
	free(var);
	return (val);
}

void	replace_env_vars(char **cont)
{
	int		i;
	int		n;
	char	**val;

	i = -1;
	while ((*cont)[++i])
	{
		if ((*cont)[i] == '$')
		{
			n = i + 1;
			if ((*cont)[++n] == '?')
				n++;
			else
				while (ft_isalnum((*cont)[n]))
					n++;
			val = get_val_env_free(ft_substr(*cont, i + 1, n - i - 1));
			*cont = delete_str_pos(i, n - i, *cont);
			if (val != NULL)
			{
				*cont = paste_str_pos(i, *cont, *val);
				i += ft_strlen(*val) - 1;
			}
		}
	}
}
