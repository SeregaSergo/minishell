/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:38:16 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 16:38:44 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_pipes(t_cmd **cmds, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i != (n - 1))
		{
			cmds[i]->pipe_out = (int *)malloc(2 * sizeof(int));
			if (cmds[i]->pipe_out == NULL)
				ft_error(ER_MEMORY);
			if (pipe(cmds[i]->pipe_out) < 0)
				ft_error(ER_PIPE);
			pipe(cmds[i]->pipe_out);
		}
		if (i != 0)
			cmds[i]->pipe_in = cmds[i - 1]->pipe_out;
		i++;
	}
}

void	close_pipes(t_cmd **cmds, int n, int i_save)
{
	int	i;

	i = 0;
	while (i < n && n != 1)
	{
		if (i != i_save && cmds[i]->pipe_in != NULL)
			close(cmds[i]->pipe_in[0]);
		if (i != i_save && cmds[i]->pipe_out != NULL)
			close(cmds[i]->pipe_out[1]);
		if (i != (i_save + 1) && cmds[i]->pipe_in != NULL)
			close(cmds[i]->pipe_in[1]);
		if (i != (i_save - 1) && cmds[i]->pipe_out != NULL)
			close(cmds[i]->pipe_out[0]);
		i++;
	}
}
