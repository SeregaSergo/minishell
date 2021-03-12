/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:05:44 by bswag             #+#    #+#             */
/*   Updated: 2021/03/12 19:36:00 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include <sys/errno.h>
#include <signal.h>
#include <term.h>
#include <termios.h>
#include <curses.h>

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

# define PROMPT			"USER"

# define ER_MEMORY			1
# define ER_ARGS			2
# define ER_NO_TERMINAL		3
# define ER_ENV_TERM		4

typedef struct termios t_termios;

typedef struct		s_glob
{
	char		*prompt;
	t_list		*cmd_lines;
	t_termios	*saved_term;
	t_termios	*term;
	char		**env;
	char		*buf;
}					t_glob;

t_glob	*g_main;

typedef struct	s_cmd_line
{
	int		cmd_space;
	int		num_cmds;
	char	**cmds;
}				t_cmd_line;

typedef struct	s_cmd
{
	int		arg_space;
	int		num_arg;
	char	**args;
	char	*out_file;
	int		out_append;
	char	*in_file;
}				t_cmd;

void	add_argument(t_cmd *cmd, char *arg);
t_cmd	*construct_cmd(void);

/*
** File: init.c
*/
void	switch_off_signals(void);
char	*get_prompt(char * param, char *prog);

/*
** File: errors.c
*/
void	ft_error(unsigned char er);

/*
** File: utility_func.c
*/
void	print_envp(char **envp);

/*
** File: utility_func.c
*/
void	switch_off_signals(void);
void	init_glob_struct(char **argv);

/*
** File: debug.c
*/
void	debug_print_buf(void);
void	debug_print_info_terminal(void);
void	debug_print_termios(void);

#endif
