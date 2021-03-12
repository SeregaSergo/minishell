/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:03:35 by bswag             #+#    #+#             */
/*   Updated: 2021/03/12 17:25:41 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(unsigned char er)
{
	ft_printf("Error: ");
	if (er == ER_ARGS)
		ft_printf("You passed incorrect number of arguments.\n");
	else if (er == ER_MEMORY)
		ft_printf("Not enough memmory to allocate.\n");
	else if (er == ER_NO_TERMINAL)
		ft_printf("Shell is not connected to the terminal.\n");
	else if (er == ER_ENV_TERM)
		ft_printf("The environment variable \"TERM\" doesn`t exist or current \
		terminal isn`t in termcap base. Check \"TERM\" variable.\n");
	exit(1);
}