/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:03:35 by bswag             #+#    #+#             */
/*   Updated: 2021/03/04 23:16:33 by bswag            ###   ########.fr       */
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
	exit(1);
}