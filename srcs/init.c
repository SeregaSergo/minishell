/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:23:49 by bswag             #+#    #+#             */
/*   Updated: 2021/03/12 16:03:08 by bswag            ###   ########.fr       */
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
		write(0, "\b\b  \b\b\n", 7);
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

/*
** Function initiates prompt by looking for (param) among environment parameters.
** If env doesn't consist it then sets prompt as (prog).
*/
char	*get_prompt(char *param, char *prog)
{
	int	i;
	char *ret;
	
	i = 0;
	if ((ret = getenv(param)) == NULL)
		return (ft_strdup(prog));
	else
		return (ret);
}