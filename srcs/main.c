/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:25:10 by bswag             #+#    #+#             */
/*   Updated: 2021/05/15 19:09:18 by bswag            ###   ########.fr       */
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
	ft_printf("%s", g_main->prompt);
	tputs(tgetstr("ks", 0), 1, ft_putchar);
	get_cursor_position(0, &g_main->cur_row, &g_main->cur_col);
}

/*
** Switch back to canonical mode, same comand to history, nulify buffer
*/
void	end_of_reading(void)
{
	tputs(tgetstr("ke", 0), 1, ft_putchar);
	tcsetattr(0, TCSAFLUSH, g_main->saved_term);
	g_main->cur_elem = g_main->history;
	g_main->cur_elem->cont = g_main->cur_buf;
	g_main->cur_buf = NULL;
	g_main->n_symb_buf = 0;
	g_main->pos = 0;
}

void	clear_cmd_line(t_cmd_line *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_line->num_cmds)
	{
		j = 0;
		while (j < cmd_line->cmds[i]->num_args)
		{
			free(cmd_line->cmds[i]->args[j]);
			j++;
		}
		free(cmd_line->cmds[i]->args);
		ft_lstclear(&cmd_line->cmds[i]->redir_in, free_token);
		ft_lstclear(&cmd_line->cmds[i]->redir_out, free_token);
		if (cmd_line->cmds[i]->pipe_out != NULL)
			free(cmd_line->cmds[i]->pipe_out);
		i++;
	}
	free(cmd_line->cmds);
	free(cmd_line);
}

int		main(int argc, char **argv, char **envp)
{
	t_tok		**lex;
	t_cmd_line	*cmd_line;
	
	if (argc != 1 && envp != NULL)
		ft_error(ER_ARGS);
	// setenv("TERM", "xterm-256color", 0); // FOR DEBUG IN VSCODE
	switch_off_signals();
	init_glob_struct(argv, envp);
	while (1)
	{
		prepare_to_read();
		if (shell_reading() == 0)
			break ;
		end_of_reading();
		lex = tokenize_input(g_main->history->cont);
		while (lex)
		{
			cmd_line = parse_input(&lex);
			// debug_print_cmd_line(cmd_line);
			execute_cmd_line(cmd_line);
			clear_cmd_line(cmd_line);
		}
	}
	tcsetattr(0, TCSAFLUSH, g_main->saved_term);
	save_history();
	return (0);
}
