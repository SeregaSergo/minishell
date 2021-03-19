/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:05:44 by bswag             #+#    #+#             */
/*   Updated: 2021/03/19 19:12:12 by bswag            ###   ########.fr       */
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
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

/*
** Program settings
*/
# define PROMPT			"USER"
# define FILE_HISTORY	"/.minishell_history"
# define FILE_HIST_2	"./.minishell_history"
# define RECORD_LIMIT	500


/*
** Error defines
*/
# define ER_MEMORY			1
# define ER_ARGS			2
# define ER_NO_TERMINAL		3
# define ER_ENV_TERM		4
# define ER_OPEN			5

/*
** Lexer defines
*/
# define SPECIAL_SYMBLS		";|><\"\'\\$"
# define STOP_SYMBLS		";|><\"\' "
# define SINGLE_TOKENS		";|<"

/*
** Token types
*/
# define TOKEN_NONE			0
# define TOKEN_PIPE			1
# define TOKEN_SEPARATOR	2
# define TOKEN_IN			3
# define TOKEN_OUT			4
# define TOKEN_OUT_APP		5
# define TOKEN_GENERAL		6
# define TOKEN_DQOUTE		7
# define TOKEN_QOUTE		8

typedef struct termios	t_termios;

typedef struct	s_env
{
	char		*var;
	char		*cont;
}				t_env;

typedef struct	s_glob
{
	char		*prompt;
	t_termios	*saved_term;
	t_termios	*term;
	t_env		**env;
	t_bdlist	*history;
	t_bdlist	*cur_elem;  // current editabe element of history list
	char		*cur_buf;	// current buf (copy of cur_elem.content)
	int			pos;
	int			n_symb_buf;
	int			num_input_cmds;
	int			i_result_prev_cmd;
	char		*c_result_prev_cmd;
}				t_glob;

t_glob			*g_main;

typedef struct	s_cmd
{
	int			num_args;
	char		**args;
	char		*out_file;
	int			out_append;
	char		*in_file;
}				t_cmd;

typedef struct	s_cmd_line
{
	int			num_cmds;
	t_cmd		**cmds;
}				t_cmd_line;

typedef struct	s_tok
{
	char		*cont;
	int			type;
}				t_tok;

/*
** File: signals.c
*/
void	switch_off_signals(void);

/*
** File: errors.c
*/
void	ft_error(unsigned char er);

/*
** File: utility_func.c
*/
void	print_env(void);
int		array_size(void **arr);
void	copy_array(void **dst, void **src);
char	**get_val_env(char *var);

/*
** File: init.c
*/
void	init_glob_struct(char **argv, char **envp);
void	set_result_prev_cmd(int	res);

/*
** File: debug.c
*/
void	debug_print_buf(void);
void	debug_print_info_terminal(void);
void	debug_print_termios(t_termios *t);
void	debug_print_lex(t_tok **lex);
void	debug_print_envp(char **envp);

/*
** File: reading.c
*/
int		shell_reading(void);
char	*paste_char_pos(int pos, char *buf, char *c);
char	*delete_char_pos(int pos, char *buf);
char	*delete_str_pos(int pos, int n_symbols, char *buf);
char	*paste_str_pos(int pos, char *buf, char *s);

/*
** File: keys_actions.c
*/
void    process_key_up(void);
void	process_key_down(void);
void    process_key_left(void);
void	process_key_right(void);
void	process_key_backspace(void);
int		process_key_eof(void);
void	process_printable_char(char *c);
int		process_key_newln(void);

/*
** File: history.c
*/
void	retrieve_history(t_bdlist **history);
void	save_history(void);

/*
** File: parser.c
*/
t_cmd_line	*parse_input(t_tok ***lex);

/*
** File: lexer.c
*/
t_tok	**tokenize_input(char *s);

/*
** File: fixer.c
*/
void	fix_lexeme(t_tok *lex);

#endif
