/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 20:00:38 by bswag             #+#    #+#             */
/*   Updated: 2021/05/25 15:24:58 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Paste string (s) into string (buf) at position (pos).
** Free buf.
*/
char	*paste_str_pos(int pos, char *buf, char *s)
{
	int		len_b;
	char	*new;
	int		len_c;

	if (buf != NULL)
		len_b = ft_strlen(buf);
	else
		len_b = 0;
	len_c = ft_strlen(s);
	new = malloc(sizeof(char) * (len_b + len_c + 1));
	if (!new)
		ft_error(ER_MEMORY);
	ft_strlcpy(new, buf, pos + 1);
	ft_strlcpy(&new[pos], s, len_c + 1);
	ft_strlcpy(&new[pos + len_c], &buf[pos], len_b - pos + 1);
	free(buf);
	return (new);
}

/*
** Delete char in string (buf) at position (pos).
** Free buf.
*/
char	*delete_str_pos(int pos, int n_symbols, char *buf)
{
	int		len;
	char	*new;

	len = ft_strlen(buf);
	new = (char *)malloc(sizeof(char) * (len + 1 - n_symbols));
	if (!new)
		ft_error(ER_MEMORY);
	ft_strlcpy(new, buf, pos + 1);
	ft_strlcpy(&new[pos], &buf[pos + n_symbols], len - pos + 1 - n_symbols);
	free(buf);
	return (new);
}

int	process_input_chars(char *c)
{
	if (!ft_strncmp(c, tgetstr("ku", 0), 4))
		process_key_up();
	else if (!ft_strncmp(c, tgetstr("kd", 0), 3))
		process_key_down();
	else if (!ft_strncmp(c, tgetstr("kr", 0), 3))
		process_key_right();
	else if (!ft_strncmp(c, tgetstr("kl", 0), 3))
		process_key_left();
	else if (c[0] == 127)
		process_key_backspace();
	else if (!ft_strncmp(c, "\n", 1))
		return (process_key_newln());
	else if (!ft_strncmp(c, "\4", 1))
		return (process_key_eof());
	else if (ft_isprint(c[0]))
		process_printable_char(c);
	return (0);
}

int	shell_reading(void)
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
