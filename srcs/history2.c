/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:36:31 by bswag             #+#    #+#             */
/*   Updated: 2021/05/18 17:00:41 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_file_name(void)
{
	char	*str;

	str = getenv("HOME");
	if (str == NULL)
		return (NULL);
	else
		str = ft_strjoin(str, FILE_HISTORY);
	return (str);
}

int	open_hist_file(int flags)
{
	char	*file;
	int		fd;

	file = get_full_file_name();
	fd = open(file, flags, 0600);
	if (fd == -1)
		fd = open(FILE_HIST_2, flags, 0600);
	if (file != NULL)
		free(file);
	return (fd);
}
