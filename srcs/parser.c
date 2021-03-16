/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:58:34 by bswag             #+#    #+#             */
/*   Updated: 2021/03/16 22:57:58 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		pass_witespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int		get_next_token(char *s)
{
	int	i;
	int	mode;


}

void	add_to_lex_arr(char ***lex, char *token)
{
	int		len;
	char	**temp;
	
	len = array_size(*lex);
	if (!(temp = (char **)malloc(sizeof(char *) * (len + 2))))
		ft_error(ER_MEMORY);
	copy_array(temp, *lex);
	if (len != 0)
		free(*lex);
	temp[len] = token;
	temp[len + 1] = NULL;
	*lex = temp;
}

char	**tokenize_input(char *s)
{
	char	**lex;
	int		i;
	int		len;
	
	i = 0;
	lex = NULL;
	while (s[i])
	{
		i += pass_witespaces(&s[i]);
		len = get_next_token(&s[i]);
		add_to_lex_arr(&lex, ft_substr(s, i, len));
		i += len;
		i += pass_witespaces(&s[i]);
	}
}

void	parse_input(void)
{
	const char	*str;
	char		**lex;
	
	str = g_main->history->cont;
	lex = tokenize_input(str);
	
}