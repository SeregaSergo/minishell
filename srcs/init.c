/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:23:49 by bswag             #+#    #+#             */
/*   Updated: 2021/03/04 22:48:17 by bswag            ###   ########.fr       */
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
	ft_printf("%s%% ", g_prompt);
}

void	switch_off_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGQUIT, sig_handler);
}

/*
** Function initiates prompt by looking for (param) among environment parameters.
** If env doesn't consist it then sets prompt as (prog).
*/
char	*find_envp(char *param, char **envp, char *prog)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (ft_strdup(prog));
	while (envp[i])	
	{
		if (ft_strncmp(param, envp[i], ft_strlen(param)) == 0)
			return (ft_strdup(&envp[i][ft_strlen(param)]));
		i++;
	}
	return (ft_strdup(prog));
}