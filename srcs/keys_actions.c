/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:55:02 by bswag             #+#    #+#             */
/*   Updated: 2021/03/15 22:44:32 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Terminal: restore position of cursor at start, delete everything at right,
**           writing previous comand on the screen if there is such.
** History:  saving current buffer in history.
*/
void    process_key_up(void)
{
	if (g_main->cur_elem->next != NULL)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		if (g_main->cur_elem->cont != NULL)
			free(g_main->cur_elem->cont);
		g_main->cur_elem->cont = g_main->cur_buf;
		g_main->cur_elem = g_main->cur_elem->next;
		if (g_main->cur_elem->cont != NULL)
		{
			g_main->cur_buf = ft_strdup(g_main->cur_elem->cont);
			g_main->n_symb_buf = ft_strlen(g_main->cur_buf);
			g_main->pos = g_main->n_symb_buf;
			write(0, g_main->cur_buf, g_main->n_symb_buf);
		}
		else
		{
			g_main->cur_buf = NULL;
			g_main->n_symb_buf = 0;
			g_main->pos = 0;
		}
	}
}

/*
** Terminal: restore position of cursor at start, delete everything at right,
**           writing next comand on the screen if there is such.
** History:  saving current buffer in history.
*/
void	process_key_down(void)
{
	if (g_main->cur_elem->prev != NULL)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		if (g_main->cur_elem->cont != NULL)
			free(g_main->cur_elem->cont);
		g_main->cur_elem->cont = g_main->cur_buf;
		g_main->cur_elem = g_main->cur_elem->prev;
		if (g_main->cur_elem->cont != NULL)
		{
			g_main->cur_buf = ft_strdup(g_main->cur_elem->cont);
			g_main->n_symb_buf = ft_strlen(g_main->cur_buf);
			g_main->pos = g_main->n_symb_buf;
			write(0, g_main->cur_buf, g_main->n_symb_buf);
		}
		else
		{
			g_main->cur_buf = NULL;
			g_main->n_symb_buf = 0;
			g_main->pos = 0;
		}
	}
}

void    process_key_left(void)
{
	if (g_main->pos > -1)
    {
		tputs(tgetstr("le", 0), 1, ft_putchar);
		g_main->pos--;
	}
}

void	process_key_right(void)
{
    if (g_main->pos < g_main->n_symb_buf)
    {
		tputs(tgetstr("nd", 0), 1, ft_putchar);
		g_main->pos++;
	}
}

// void	process_key_backspace(char *c)
// {
    
// }

int	process_key_eof(void)
{
    if (g_main->n_symb_buf == 0)
		return (1);
	else
		return (0);
}

int	process_printable_char(char *c)
{
    write(0, c, 1);
	if (!ft_strncmp(c, "\n", 1))
		return (1);
	g_main->cur_buf = paste_char_pos(g_main->pos, g_main->cur_buf, c);
	g_main->pos++;
	g_main->n_symb_buf++;
	return (0);
}