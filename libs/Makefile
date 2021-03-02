# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <bswag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 17:19:13 by bswag             #+#    #+#              #
#    Updated: 2021/03/02 20:08:52 by bswag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libft_shell.a
SRCS =		get_next_line.c \
			get_next_line_utils.c
PATHSRC =	./GNL/
OBJS =	$(SRCS:%.c=%.o)
LIB =		libft.a
PATHLIB = ./libft/
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
DEPS = $(PATHSRC)get_next_line.h

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(addprefix $(PATHSRC),$(OBJS)) $(LIB)
	cp $(PATHLIB)$(LIB) ./$(NAME)
	ar -rcs $(NAME) $(addprefix $(PATHSRC),$(OBJS))

$(LIB):
	$(MAKE) -C $(PATHLIB)

%.o: $(PATHSRC)%.c $(DEPS)
	$(CC) $(CFLAGS) -o $(PATHSRC)$@ $<
	
bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
