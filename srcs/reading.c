/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 20:00:38 by bswag             #+#    #+#             */
/*   Updated: 2021/03/15 16:03:09 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int			ft_read(t_fd_data *fd_data, char *buf)
// {
// 	int		chars;
// 	char	*tmp_str;

// 	chars = read(fd_data->fd, buf, BUFFER_SIZE);
// 	if (chars < 0)
// 		return (chars);
// 	buf[chars] = '\0';
// 	if (!(tmp_str = gnl_strjoin(fd_data->rem, buf)))
// 		return (-1);
// 	free(fd_data->rem);
// 	fd_data->rem = tmp_str;
// 	return (chars);
// }

// void	add_chars_to_buf(char *c)
// {
	
// }

void	process_input_chars(char *c)
{
	if (!ft_strncmp(c, "\033[A", 3))			// UP
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		print_previous_cmd();
	}
	else if (!ft_strncmp(c, "\033[B", 3))		// DOWN
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", 0), 1, ft_putchar);
		print_next_cmd();
	}
	// else if (!ft_strncmp(c, "\033[C", 3))		// RIGHT
	// {
		
	// }
	// else if (!ft_strncmp(c, "\033[D", 3))		// LEFT
	// {
		
	// }
	// else if (!ft_strncmp(c, key_backspace, 4))	// Backspace
	// {
		
	// }
	else
	{
		write(0, c, 1);
		// add_chars_to_buf(c);
	}
}

int     shell_reading(void)
{
	int			rd;
	char		*buf;
	char		*c;
	// int			n_symbls;

	buf = *(g_main->cur_buf);
	c = g_main->c;
	c[0] = 0;
	rd = 0;
	while (!ft_strchr(c, '\n') && !ft_strchr(c, '\4'))
	{
		rd = read(0, c, 63);
		c[rd] = 0;
		process_input_chars(c);
	}
	return (ft_strlen(buf));
}