/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 20:00:38 by bswag             #+#    #+#             */
/*   Updated: 2021/03/15 22:44:02 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Paste string (c) into string buf at position (pos).
** Free buf.
*/
char	*paste_char_pos(int pos, char *buf, char *c)
{
	int		len_b;
	char	*new;
	int		len_c;
	
	if (buf != NULL)
		len_b = ft_strlen(buf);
	else
		len_b = 0;
	len_c = ft_strlen(c);
	if (!(new = malloc(sizeof(char) * (len_b + len_c + 1))))
		ft_error(ER_MEMORY);
	ft_strlcpy(new, buf, pos + 1);
	ft_strlcpy(&new[pos], c, len_c + 1);
	ft_strlcpy(&new[pos + len_c], &buf[pos], len_b - pos + 1);
	free(buf);
	return (new);
}

int	process_input_chars(char *c)
{
	if (!ft_strncmp(c, "\033[A", 3))
		process_key_up();
	else if (!ft_strncmp(c, "\033[B", 3))
		process_key_down();
	else if (!ft_strncmp(c, "\033[C", 3))
		process_key_right();
	else if (!ft_strncmp(c, "\033[D", 3))
		process_key_left();
	// else if (!ft_strncmp(c, key_backspace, 4))
	// 	process_key_backspace(c);
	else if (!ft_strncmp(c, "\4", 1))
		return (process_key_eof());
	else if (ft_isprint(c[0]))
		return (process_printable_char(c));
	return (0);
}

int     shell_reading(void)
{
	int			rd;
	char		c[64];

	c[0] = 0;
	rd = 0;
	while (1)
	{
		rd = read(0, c, 63);
		c[rd] = 0;
		if (process_input_chars(c) == 1)
			break ;
	}
	return (g_main->n_symb_buf);
}