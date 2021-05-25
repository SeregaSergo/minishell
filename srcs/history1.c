/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:36:31 by bswag             #+#    #+#             */
/*   Updated: 2021/05/25 15:21:56 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_records(t_bdlist **new_hist)
{
	t_bdlist	*last_elem;
	t_bdlist	*tmp;

	last_elem = ft_bdlstfind(g_main->history, g_main->num_input_cmds - 1);
	tmp = last_elem->next;
	last_elem->next = *new_hist;
	if (*new_hist != NULL)
		(*new_hist)->prev = last_elem;
	*new_hist = g_main->history;
	g_main->history = tmp;
	if (g_main->history != NULL)
		g_main->history->prev = NULL;
	tmp = NULL;
}

void	retrieve_history(t_bdlist **history)
{
	int			fd;
	char		*line;
	t_bdlist	*new;

	*history = NULL;
	line = NULL;
	fd = open_hist_file(O_RDONLY | O_CREAT);
	if (fd != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			new = ft_bdlstnew(line);
			if (!new)
				ft_error(ER_MEMORY);
			ft_bdlstadd_front(history, new);
		}
		if (line != NULL)
			free(line);
		close(fd);
	}
}

void	write_history(t_bdlist *last_elem)
{
	int	fd;

	fd = open_hist_file(O_WRONLY | O_TRUNC);
	if (fd != -1)
	{
		while (last_elem)
		{
			if (last_elem->cont != NULL)
			{
				if (last_elem->prev != NULL)
					ft_putendl_fd(last_elem->cont, fd);
				else
					ft_putstr_fd(last_elem->cont, fd);
			}
			last_elem = last_elem->prev;
		}
		close(fd);
	}
}

void	save_history(void)
{
	t_bdlist	*new_hist;

	if (g_main->num_input_cmds > 0)
	{
		retrieve_history(&new_hist);
		add_new_records(&new_hist);
		write_history(ft_bdlstfind(new_hist, RECORD_LIMIT - 1));
		if (g_main->history->cont)
			free(g_main->history->cont);
	}
}
