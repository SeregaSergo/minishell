/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 21:08:25 by bswag             #+#    #+#             */
/*   Updated: 2021/03/24 14:23:21 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		rd(int fd)
{
	unsigned char   buffer[4];
	ssize_t         n;

	n = read(fd, buffer, 1);
	if (n > (ssize_t)0)
		return buffer[0];
	else
		return (-1);
}

int		wr(int fd, char *data, size_t bytes)
{
	ssize_t		n;

	n = write(fd, data, bytes);
	if (n > (ssize_t)0)
		return (0);
	else
		return (-1);
}

/* As the tty for current cursor position.
 * This function returns 0 if success, errno code otherwise.
 * Actual errno will be unchanged.
*/
int get_cursor_position(int tty, int *rowptr, int *colptr)
{
	int	result;

	if (wr(tty, "\033[6n", 4))
		return (1);
	if (rd(tty) != 27 || rd(tty) != '[')
		return (1);
	*rowptr = 0;
	result = rd(tty);
	while (result >= '0' && result <= '9')
	{
		*rowptr = 10 * (*rowptr) + result - '0';
		result = rd(tty);
	}
	if (result != ';')
		return (1);
	*colptr = 0;
	result = rd(tty);
	while (result >= '0' && result <= '9')
	{
		*colptr = 10 * (*colptr) + result - '0';
		result = rd(tty);
	}
	if (result != 'R')
		return (1);
	return (0);
}

void	restore_cursor_pos(void)
{
	char	*str;
	int		col;
	int		row;
	int		ln;
	
	get_cursor_position(0, &row, &col);
	ln = (g_main->n_symb_buf + g_main->cur_col - 2) / tgetnum("co");
	ln = ln - (row - g_main->cur_row);
	str = tgoto(tgetstr("cm", 0), g_main->cur_col - 1 , g_main->cur_row - ln - 1);
	tputs(str, 1, ft_putchar);
}