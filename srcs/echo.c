/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:14:45 by egilbert          #+#    #+#             */
/*   Updated: 2021/03/29 20:45:05 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    echo(t_shell *bash)
{
    int i;

    i = -1;
    while (bash->echo[++i])
        write(1, &bash->echo[i], 1);
    if (!bash->minus_n)
        write(1, "\n", 1);
}
