/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:30:37 by bswag             #+#    #+#             */
/*   Updated: 2021/03/12 20:23:12 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int	sig)
{
	if (sig > 0)
		write(0, "\b\b  \b\b", 6);
}

void	sigint_handler(int	sig)
{
	if (sig > 0)
		// write(0, "\b\b  \b\b\n", 7);
	ft_printf("%s%% ", g_main->prompt);
}

void	switch_off_signals(void)
{
	// signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGQUIT, sig_handler);
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGTSTP, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
}