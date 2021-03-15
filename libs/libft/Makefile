# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <bswag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 14:09:47 by bswag             #+#    #+#              #
#    Updated: 2021/03/15 20:28:15 by bswag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_strlcat.c \
	   ft_isprint.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_strlcpy.c \
	   ft_isascii.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_strlen.c \
	   ft_bzero.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strncmp.c \
	   ft_strnstr.c \
	   ft_atoi.c \
	   ft_memset.c \
	   ft_memcpy.c \
	   ft_memccpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_itoa_base.c \
	   ft_strtoupper.c \
	   ft_lutoa_base.c \
	   ft_write_param.c \
	   ft_strchr_null.c \
	   ft_char_in_set.c \
	   ft_str_content.c \
	   ft_putchar.c
SRCSBNS = ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \
		  ft_bdlstnew.c \
		  ft_bdlstadd_front.c \
		  ft_bdlstsize.c
OBJS = $(SRCS:%.c=%.o)
OBJSBNS = $(SRCSBNS:%.c=%.o)
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
DEPS = libft.h

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(OBJSBNS)
	ar -rcs $(NAME) $(OBJS) $(OBJSBNS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f $(OBJS) $(OBJSBNS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
