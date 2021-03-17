/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:58:34 by bswag             #+#    #+#             */
/*   Updated: 2021/03/17 23:57:38 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(void)
{
	char	*str;
	t_tok	**lex;
	
	str = g_main->history->cont;
	lex = tokenize_input(str);
	// fix_lexemes(lex);
	debug_print_lex(lex);
}