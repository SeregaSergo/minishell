/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:25:10 by bswag             #+#    #+#             */
/*   Updated: 2021/03/12 16:32:34 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_term(void)
{
	ft_printf("ICANON = %d\n", ((g_main->saved_term->c_lflag & ICANON) > 0) ? 1 : 0);
	ft_printf("ISIG = %d\n", ((g_main->saved_term->c_lflag & ISIG) != 0) ? 1 : 0);
	ft_printf("IEXTEN = %d\n", ((g_main->saved_term->c_lflag & IEXTEN) != 0) ? 1 : 0);
	ft_printf("ECHO = %d\n", ((g_main->saved_term->c_lflag & ECHO) != 0) ? 1 : 0);
	ft_printf("ECHOE = %d\n", ((g_main->saved_term->c_lflag & ECHOE) > 0) ? 1 : 0);
	ft_printf("ECHOK = %d\n", ((g_main->saved_term->c_lflag & ECHOK) > 0) ? 1 : 0);
	ft_printf("ECHONL = %d\n", ((g_main->saved_term->c_lflag & ECHONL) > 0) ? 1 : 0);
	ft_printf("NOFLSH = %d\n", ((g_main->saved_term->c_lflag & NOFLSH) > 0) ? 1 : 0);
	ft_printf("TOSTOP = %d\n", ((g_main->saved_term->c_lflag & TOSTOP) > 0) ? 1 : 0);
	ft_printf("\nSymbols in cc_t\n");
	ft_printf("VINT = %d\n", g_main->saved_term->c_cc[VINTR]);
	ft_printf("VEOF = %d\n", g_main->saved_term->c_cc[VEOF]);
	ft_printf("VEOL = %d\n", g_main->saved_term->c_cc[VEOL]);
	ft_printf("VERASE = %d\n", g_main->saved_term->c_cc[VERASE]);
	ft_printf("VKILL = %d\n", g_main->saved_term->c_cc[VKILL]);
}

void	debug_print_buf(void)
{
	int	i = 0;

	while (g_main->buf[i])
	{
		ft_printf("#%i: %d\n", i, g_main->buf[i]);
		i++;
	}
}

/*
** Switch to noncanonical mode, nullifies buffer pointer, print prompt
*/
void	prepare_to_read(void)
{
	tcsetattr(0, TCSAFLUSH, g_main->term);
	g_main->buf = NULL;
	ft_printf("%s%% ", g_main->prompt);
}

/*
** Switch back to canonical mode, free buffer
*/
void	end_of_reading(void)
{
	tcsetattr(0, TCSAFLUSH, g_main->saved_term);
	free(g_main->buf);
}

/*
** Initiate global structure g_main.
** Try to set prompt string according to env parameter defined in minishell.h
** as PROMPT, if there is no such parameter then set as program name. 
*/
void	init_glob_struct(char **argv)
{
	if ((g_main = (t_glob *)malloc(sizeof(t_glob))) == NULL)
		ft_error(ER_MEMORY);
	if ((g_main->saved_term = (t_termios *)malloc(sizeof(t_termios))) == NULL)
		ft_error(ER_MEMORY);
	if ((g_main->term = (t_termios *)malloc(sizeof(t_termios))) == NULL)
		ft_error(ER_MEMORY);
	tcgetattr(0, g_main->saved_term);
	ft_memcpy(g_main->term, g_main->saved_term, sizeof(t_termios));
	g_main->term->c_lflag &= ~ICANON;
	g_main->term->c_cc[VMIN] = 1;
	g_main->term->c_cc[VTIME] = 0;
	debug_print_term();
	g_main->prompt = get_prompt(PROMPT, ft_strrchr(argv[0], '/') + 1);
	g_main->cmd_lines = NULL;
}

int		main(int argc, char **argv, char **envp)
{
	int		res;
	
	if (argc != 1 && envp != NULL)
		ft_error(ER_ARGS);
	switch_off_signals();
	init_glob_struct(argv);
	while (1)
	{
		prepare_to_read(); 			// switch to noncanonical mode, null buf, prompt
		res = get_next_line(0, &g_main->buf);
		ft_printf("len buf = %d\n", ft_strlen(g_main->buf));
		if (res <= 0 && g_main->buf[0] == '\0')
		{
			ft_printf("\n");
			exit(0);
		}
		debug_print_buf();
		// parse_input();
		end_of_reading();			// switch back to canonical mode, free buf
		// execute_comands();
		// clear_struct();
	}
	return (0);
}

// int		get_term_info(char *buf, char **envp)
// {
// 	char	*termtype;
	
// 	if (!isatty(STDIN_FILENO))
//         return (1);
//     termtype = ft_getenv("TERM", envp);
// 	ft_printf("%s\n", termtype);
//     if (termtype == NULL || tgetent(buf, termtype) != 1)
//     {
// 		ft_putstr_fd("Can not find terminal or termcap base. ", 2);
// 		ft_putendl_fd("Please, choose one and define the \"TERM\" variable", 2);
//     	return (1);
//     }
// 	return (0);
// }

// void        test_tgetnum(void)
// {
// 	int	col;
// 	int	li;
	
// 	col = tgetnum("co");
// 	li = tgetnum("li");
// 	ft_printf("Columns = %d, lines = %d\n", col, li);
// }

// void	print_envp(char **envp)
// {
// 	int	i;
	
// 	i = 0;
// 	if (envp != NULL)
// 	{
// 		while (envp[i])	
// 		{
// 			ft_printf("%s\n", envp[i]);
// 			i++;
// 		}
// 	}
// }

// int		main(int argc, char **argv, char **envp)
// {
// 	// int		res;
// 	// char	*buf;
//     // char			buf_termtype[2048]; //2048
// 	struct termios	term;

// 	if (argc != 1)
// 		ft_error(ER_ARGS);
// 	// print_envp(envp);
// 	g_prompt = get_prompt("USER", envp, &argv[0][2]);
// 	// if (get_term_info(buf_termtype, envp))
// 		// return (1);
// 	// test_tgetnum();
	
// 	tcgetattr(0, &term);
// 	print_cflags(term);

// 	term.c_lflag &= ~ICANON;
// 	tcsetattr (0, TCSAFLUSH, &term);
// 	ft_printf("\n");
// 	print_cflags(term);
// 	term.c_lflag |= ICANON;
// 	tcsetattr (0, TCSAFLUSH, &term);
// 	return (0);
// }