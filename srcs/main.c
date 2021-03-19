/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:25:10 by bswag             #+#    #+#             */
/*   Updated: 2021/03/19 14:26:43 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Switch to noncanonical mode, making new element in history, print prompt
*/
void	prepare_to_read(void)
{
	t_bdlist	*new;
	
	tcsetattr(0, TCSAFLUSH, g_main->term);
	if (!(new = ft_bdlstnew(NULL)))
		ft_error(ER_MEMORY);
	ft_bdlstadd_front(&g_main->history, new);
	g_main->cur_elem = g_main->history;
	ft_printf("%s%% ", g_main->prompt);
	tputs(save_cursor, 1, ft_putchar);
}

/*
** Switch back to canonical mode, same comand to history, nulify buffer
*/
void	end_of_reading(void)
{
	tcsetattr(0, TCSAFLUSH, g_main->saved_term);
	g_main->cur_elem = g_main->history;
	g_main->cur_elem->cont = g_main->cur_buf;
	g_main->cur_buf = NULL;
	g_main->n_symb_buf = 0;
	g_main->pos = 0;
}

int		main(int argc, char **argv, char **envp)
{
	t_tok		**lex;
	// t_cmd_line	*cmd_line;
	
	if (argc != 1 && envp != NULL)
		ft_error(ER_ARGS);
	// setenv("TERM", "xterm-256color", 0);
	switch_off_signals();
	init_glob_struct(argv, envp);
	print_env();
	while (1)
	{
		prepare_to_read();
		if (shell_reading() == 0)
			break ;
		end_of_reading();
		lex = tokenize_input(g_main->history->cont);
		debug_print_lex(lex);
		// while (is_there_comand(lex))
		// {
		// 	cmd_line = parse_input(lex);
		// 	execute_cmd_line(cmd_line);
		// }
	}
	tcsetattr(0, TCSAFLUSH, g_main->saved_term);
	save_history();
	return (0);
}
