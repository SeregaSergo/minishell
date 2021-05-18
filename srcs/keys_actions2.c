/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_actions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:55:02 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 18:48:18 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_key_backspace(void)
{
	if (g_main->pos > 0)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		g_main->pos--;
		g_main->cur_buf = delete_str_pos(g_main->pos, 1, g_main->cur_buf);
		g_main->n_symb_buf--;
	}
}

int	process_key_newln(void)
{
	if (g_main->n_symb_buf == 0)
	{
		printf("\n%s%% ", g_main->prompt);
		return (0);
	}
	else
	{
		write(1, "\n", 1);
		g_main->num_input_cmds++;
		return (1);
	}
}

int	process_key_eof(void)
{
	if (g_main->n_symb_buf == 0)
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
	else
		return (0);
}

void	process_printable_char(char *c)
{
	tputs(tgetstr("im", 0), 1, ft_putchar);
	write(1, c, 1);
	tputs(tgetstr("ei", 0), 1, ft_putchar);
	g_main->cur_buf = paste_str_pos(g_main->pos, g_main->cur_buf, c);
	g_main->pos++;
	g_main->n_symb_buf++;
}
