/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:05:44 by bswag             #+#    #+#             */
/*   Updated: 2021/05/26 00:31:10 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <sys/errno.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <dirent.h>

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
# define ER_PIPE			6
# define ER_FORK			7
# define ER_WAIT			8

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

typedef struct s_env
{
	char		*var;
	char		*cont;
}				t_env;

typedef struct s_glob
{
	char			*prompt;
	struct termios	*saved_term;
	struct termios	*term;
	t_env			**env;
	t_bdlist		*history;
	t_bdlist		*cur_elem;
	char			*cur_buf;
	int				pos;
	int				n_symb_buf;
	int				num_input_cmds;
	int				i_result_prev_cmd;
	char			*c_result_prev_cmd;
	int				cur_row;
	int				cur_col;
}					t_glob;

t_glob				*g_main;

/*
** Redirects have content type t_tok.
** They locate in list in the same order as in bash line
** cat < file1 < file2 < file3 (file1 -> file2 -> file3)
** cat > file1 >> file2 > file3 (file1 -> file2 -> file3)
*/
typedef struct s_cmd
{
	int			num_args;
	char		**args;
	t_list		*redir_in;
	t_list		*redir_out;
	int			*pipe_in;
	int			*pipe_out;
}				t_cmd;

typedef struct s_cmd_line
{
	int			num_cmds;
	t_cmd		**cmds;
}				t_cmd_line;

typedef struct s_tok
{
	char		*cont;
	int			type;
}				t_tok;

/*
** File: signals.c
*/
void		switch_off_signals(void);
void		switch_on_signals(void);
void		sig_handler(int	sig);

/*
** File: errors.c
*/
void		ft_error(unsigned char er);

/*
** File: utility_func.c
*/
int			print_env(void);
int			array_size(void **arr);
void		copy_array(void **dst, void **src);
char		**get_val_env(char *var);
void		set_result_prev_cmd(int	res);

/*
** File: init.c
*/
void		init_glob_struct(char **argv, char **envp);
t_env		*make_env_struct(char *env_elem);

/*
** File: reading.c
*/
int			shell_reading(void);
char		*delete_str_pos(int pos, int n_symbols, char *buf);
char		*paste_str_pos(int pos, char *buf, char *s);

/*
** File: keys_actions.c
*/
void		process_key_up(void);
void		process_key_down(void);
void		process_key_left(void);
void		process_key_right(void);
void		process_key_backspace(void);
int			process_key_eof(void);
void		process_printable_char(char *c);
int			process_key_newln(void);

/*
** File: history.c
*/
void		retrieve_history(t_bdlist **history);
void		save_history(void);
char		*get_full_file_name(void);
int			open_hist_file(int flags);

/*
** File: parser.c
*/
t_cmd_line	*parse_input(t_tok ***lex);
t_cmd		*create_comand(t_tok **lex, int *i);

/*
** File: lexer.c
*/
t_tok		**tokenize_input(char **s);
void		free_token(void *t);
int			get_next_token(char *s, int *type);
int			check_syntax(t_tok **lex);
void		free_token(void *t);
int			check_closed_qouts(t_tok *cont, int type);
int			syntax_error(t_tok	***lex);
int			add_to_lex_arr(t_tok ***lex, char *token_cont, int type);
int			add_to_prev_lex_arr(t_tok ***lex, char *token_cont, int type);

/*
** File: fixer.c
*/
void		fix_lexeme(t_tok *lex);
void		replace_env_vars(char **cont);

/*
** File: cursor_pos.c
*/
int			get_cursor_position(int tty, int *rowptr, int *colptr);
void		restore_cursor_pos(void);

/*
** File: execute.c
*/
void		execute_cmd_line(t_cmd_line	*cmd);
int			execute_cmd(t_cmd *cmd);

/*
** File: built-in1.c
*/
int			cd(char **path);
int			ft_echo(char **args);
int			pwd(void);
int			change_value_env(char *new, char **value);
int			is_builtin(char *cmd);
void		exec_in_the_same_proc(t_cmd *cmd);
int			exit_cmd(char **args);

/*
** File: export.c
*/
int			export(char *str);

/*
** File: unset.c
*/
int			unset(char *var);
int			var_exist(char *var);
int			ft_strcmp(char *s1, char*s2);

/*
** File: execve.c
*/
int			execve_cmds(t_cmd *cmd);

/*
** File: redirects.c
*/
int			redirect_streams(t_cmd *cmd);
int			file_redirect(t_list *files, int stream);

/*
** File: pipes.c
*/
void		make_pipes(t_cmd **cmds, int n);
void		close_pipes(t_cmd **cmds, int n, int i_save);

#endif
