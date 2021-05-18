/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:30:37 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 19:22:16 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int	sig)
{
	if (sig > 0)
		sig = 0;
}

void	sigint_handler(int	sig)
{
	if (sig > 0)
	{
		if (g_main->cur_buf != NULL)
			free(g_main->cur_buf);
		g_main->cur_buf = NULL;
		g_main->pos = 0;
		g_main->n_symb_buf = 0;
		if (g_main->history->cont)
			free(g_main->history->cont);
		g_main->history->cont = NULL;
		g_main->cur_elem = g_main->history;
		set_result_prev_cmd(1);
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(g_main->prompt, 1);
	}
}

void	switch_off_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	switch_on_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
