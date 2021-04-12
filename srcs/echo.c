/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:40:52 by egilbert          #+#    #+#             */
/*   Updated: 2021/04/01 18:30:26 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_line(char *line)
{
	while (*line)
	{
		write(1, line, 1);
		line++;
	}
}

int		ft_echo(char **args)
{
	int i;

	i = 0;
	while (args[++i])
	{
		if (i == 1 && !ft_strncmp(args[1], "-n", 2) && args[1][2] == 0)
			i++;
		if (args[i] != NULL)
			put_line(args[i]);
		if (args[i + 1] != NULL)
			write(1, " ", 1);
	}
	if (args[1] && !ft_strncmp(args[1], "-n", 2) && args[1][2] == 0)
		;
	else
		write(1, "\n", 1);
	return (0);
}
