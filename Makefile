NAME =	minishell
SRCS =	./srcs/main.c \
		./srcs/init.c \
		./srcs/errors.c \
		./srcs/parser1.c \
		./srcs/parser2.c \
		./srcs/utility_func.c \
		./srcs/signals.c \
		./srcs/reading.c \
		./srcs/keys_actions1.c \
		./srcs/keys_actions2.c \
		./srcs/history1.c \
		./srcs/history2.c \
		./srcs/lexer1.c \
		./srcs/lexer2.c \
		./srcs/lexer3.c \
		./srcs/lexer4.c \
		./srcs/fixer1.c \
		./srcs/fixer2.c \
		./srcs/cursor_pos.c \
		./srcs/execute.c \
		./srcs/built-in1.c \
		./srcs/unset.c \
		./srcs/execve.c \
		./srcs/built-in2.c \
		./srcs/redirects.c \
		./srcs/pipes.c \
		./srcs/export.c
OBJS = $(SRCS:%.c=%.o)
LIB = libft_shell.a
PATHLIB = libs/
INC = includes
CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -I$(INC) -ltermcap -lft_shell -L$(PATHLIB) $(OBJS) -o $(NAME)

$(LIB):
	$(MAKE) -C $(PATHLIB)

%.o: %.c $(INC)/minishell.h
	$(CC) -c $(CFLAGS) -I$(INC) -o $@ $<

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all