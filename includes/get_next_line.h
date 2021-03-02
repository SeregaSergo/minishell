/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:28:41 by bswag             #+#    #+#             */
/*   Updated: 2021/02/01 22:24:55 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "../libft/libft.h"

typedef struct		s_fd_data
{
	int				fd;
	char			*rem;
}					t_fd_data;

typedef struct		s_lstg
{
	t_fd_data		*content;
	struct s_lstg	*next;
}					t_lstg;

int					get_next_line(int fd, char **line);
int					gnl_strchr(const char *s, int c);
char				*gnl_substr(char const *s, unsigned int start, size_t len);
char				*gnl_strjoin(char const *s1, char const *s2);
size_t				gnl_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
