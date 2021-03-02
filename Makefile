NAME =	minishell
SRCS =	./srcs/main.c
OBJS = $(SRCS:%.c=%.o)
LIB = libft_shell.a
PATHLIB = libs/
INC = includes
CC = gcc
CFLAGS = -O2 -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -I$(INC) -lft_shell -L$(PATHLIB) $(OBJS) -o $(NAME)

$(LIB):
	$(MAKE) -C $(PATHLIB)

%.o: %.c $(INC)*
	$(CC) -c $(CFLAGS) -I$(INC) -o $@ $<

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
