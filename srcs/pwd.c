/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:14:41 by egilbert          #+#    #+#             */
/*   Updated: 2021/04/01 16:37:55 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char *line;

	line = getcwd(NULL, 1);
	write(1, line, ft_strlen(line));
	write(1,"\n", 1);
	free(line);
}
