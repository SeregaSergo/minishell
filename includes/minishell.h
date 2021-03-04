/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:05:44 by bswag             #+#    #+#             */
/*   Updated: 2021/03/04 23:09:25 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include <sys/errno.h>
#include <signal.h>

enum TokenType{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	
	TOKEN	= -1,
};

char	*g_prompt;

# define ER_MEMORY			1
# define ER_ARGS			2

typedef struct	s_exec
{
	/* data */
}				t_exec;

/*
** File: init.c
*/
void	switch_off_signals(void);
char	*find_envp(char * param, char **envp, char *prog);

/*
** File: errors.c
*/
void	ft_error(unsigned char er);

#endif
