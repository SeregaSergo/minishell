/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:23:49 by bswag             #+#    #+#             */
/*   Updated: 2021/03/15 23:49:41 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_file_name()
{
	char	*str;
	
	str = getenv("HOME");
	if (str == NULL)
		return (NULL);
	else
		str = ft_strjoin(str, FILE_HISTORY);
	return (str);
}

void	retrieve_history(void)
{
	int 		fd;
	char		*line;
	t_bdlist	*new;
	char		*file;
	
	g_main->history = NULL;
	line = NULL;
	file = get_full_file_name();
	if ((fd = open(file, O_RDONLY | O_CREAT, 0600)) > -1) ;
	else if ((fd = open(FILE_HIST_2, O_RDONLY | O_CREAT, 0600)) < 0)
		ft_error(ER_OPEN);
	(file != NULL) ? free(file) : 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(new = ft_bdlstnew(line)))
			ft_error(ER_MEMORY);
		ft_bdlstadd_front(&g_main->history, new);
	}
	if (line != NULL)
	{
		if (!(new = ft_bdlstnew(line)))
			ft_error(ER_MEMORY);
		ft_bdlstadd_front(&g_main->history, new);
	}
	g_main->cur_elem = g_main->history;
	close(fd);
}

/*
** Function initiates prompt by looking for (param) among environment parameters.
** If env doesn't consist it then sets prompt as (prog).
*/
char	*get_prompt(char *param, char *prog)
{
	int	i;
	char *ret;
	
	i = 0;
	if ((ret = getenv(param)) == NULL)
		return (ft_strdup(prog));
	else
		return (ret);
}

/*
** Loads info from about terminal from data-base.
** It can have leaks because of tgetent with NULL (allocates memory by itself)
*/
void		get_term_info(void)
{
	char	*termtype;
	
	if (!isatty(STDIN_FILENO))
        ft_error(ER_NO_TERMINAL);
    termtype = getenv("TERM");
    if (termtype == NULL || tgetent(NULL, termtype) != 1) 
		ft_error(ER_ENV_TERM);
}

/*
** Initiate global structure g_main.
** Try to set prompt string according to env parameter defined in minishell.h
** as PROMPT, if there is no such parameter then set as program name.
** Retrieve history from file ~/.minishell_history.
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
	g_main->term->c_lflag &= ~(ICANON | ECHO);
	g_main->term->c_cc[VMIN] = 1;
	g_main->term->c_cc[VTIME] = 0;
	g_main->prompt = get_prompt(PROMPT, ft_strrchr(argv[0], '/') + 1);
	g_main->cmd_lines = NULL;
	get_term_info();
	retrieve_history();
	g_main->cur_buf = NULL;
	g_main->n_symb_buf = 0;
	g_main->pos = 0;
	write(0, "HERE", 4);
	// debug_print_termios(g_main->saved_term);
	// ft_printf("\nChanged parameters\n");
	// debug_print_termios(g_main->term);
	// debug_print_info_terminal();
}