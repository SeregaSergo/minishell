/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:30:37 by bswag             #+#    #+#             */
/*   Updated: 2021/03/16 16:25:07 by bswag            ###   ########.fr       */
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
		ft_printf("\n%s%% ", g_main->prompt);
	}
}

void	switch_off_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGQUIT, sig_handler);
}