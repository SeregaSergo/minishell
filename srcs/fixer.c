/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:26:22 by bswag             #+#    #+#             */
/*   Updated: 2021/03/17 23:57:32 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	fix_lexemes(t_tok **lex)
// {
// 	int	i;

// 	i = 0;
// 	while (lex[i])
// 	{
// 		if (lex[i][0] == "\"")
// 			lex[i] = fix_dqoute(lex[i]);
// 		else if (lex[i][0] == "'")
// 			lex[i] = fix_qoute(lex[i]);
// 		else if (lex[i][0] == "'")
// 			lex[i] = fix_qoute(lex[i]);
// 		i++;
// 	}
// }