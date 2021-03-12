/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:25:10 by bswag             #+#    #+#             */
/*   Updated: 2021/03/12 20:23:02 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Switch to noncanonical mode, nullifies buffer pointer, print prompt
*/
void	prepare_to_read(void)
{
	tcsetattr(0, TCSAFLUSH, g_main->term);
	g_main->buf = NULL;
	ft_printf("%s%% ", g_main->prompt);
}

/*
** Switch back to canonical mode, free buffer
*/
void	end_of_reading(void)
{
	tcsetattr(0, TCSAFLUSH, g_main->saved_term);
	free(g_main->buf);
}

int		main(int argc, char **argv, char **envp)
{
	int		res;
	
	if (argc != 1 && envp != NULL)
		ft_error(ER_ARGS);
	switch_off_signals();
	init_glob_struct(argv);
	while (1)
	{
		prepare_to_read(); 			// switch to noncanonical mode, null buf, prompt
		res = get_next_line(0, &g_main->buf);
		if (res <= 0 || res == 2)
		{
			ft_printf("\n");
			exit(0);
		}
		debug_print_buf();
		// parse_input();
		end_of_reading();			// switch back to canonical mode, free buf
		// execute_comands();
		// clear_struct();
	}
	return (0);
}
