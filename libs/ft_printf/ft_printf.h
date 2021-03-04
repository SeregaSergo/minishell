/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:47:39 by bswag             #+#    #+#             */
/*   Updated: 2021/02/01 21:36:46 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_format
{
	unsigned char	flags;
	int				width;
	int				precision;
	char			type;
	int				length;
}					t_format;

int					ft_printf(const char *format, ...);

# define FLAG_EMPTY		0b00000000
# define FLAG_SHARP		0b00000001
# define FLAG_MINUS		0b00000010
# define FLAG_PLUS		0b00000100
# define FLAG_SPACE		0b00001000 
# define FLAG_ZERO		0b00010000

int					ft_parser(const char *format, t_format *frmt, va_list ap);
int					parse_flags(const char *format, unsigned char *flags);
int					parse_width(const char *format, t_format *frmt, va_list ap);
int					parse_type(const char *format, char *type);
int					parse_precision(const char *format, int *precision, \
					va_list ap);

void				ft_processor(t_format *frmt, va_list ap);
void				process_int(t_format *frmt, long int arg);
void				process_uxx(t_format *frmt, unsigned int arg);
void				process_p(t_format *frmt, void *arg);
void				process_str(t_format *frmt, char *arg);
void				process_char(t_format *frmt, int arg);

#endif
