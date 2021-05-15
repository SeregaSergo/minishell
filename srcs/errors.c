/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:03:35 by bswag             #+#    #+#             */
/*   Updated: 2021/05/16 01:13:48 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(unsigned char er)
{
	ft_putstr_fd("Error: ", 2);
	if (er == ER_ARGS)
		ft_putstr_fd("You passed incorrect number of arguments.\n", 2);
	else if (er == ER_MEMORY)
		ft_putstr_fd("Not enough memmory to allocate.\n", 2);
	else if (er == ER_NO_TERMINAL)
		ft_putstr_fd("Shell is not connected to the terminal.\n", 2);
	else if (er == ER_ENV_TERM)
		ft_putstr_fd("The environment variable \"TERM\" doesn`t exist or \
		current terminal isn`t in termcap base. \
		Check \"TERM\" variable.\n", 2);
	else if (er == ER_OPEN)
		ft_putstr_fd("Can't open the file.\n", 2);
	else if (er == ER_PIPE)
		ft_putstr_fd("Can't create pipe\n", 2);
	else if (er == ER_FORK)
		ft_putstr_fd("Can't create pipe\n", 2);
	else if (er == ER_WAIT)
		ft_putstr_fd("Troubles with waiting of child process\n", 2);
	save_history();
	if (g_main->saved_term)
		tcsetattr(0, TCSAFLUSH, g_main->saved_term);
	exit(errno);
}
