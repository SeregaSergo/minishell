/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:23:49 by bswag             #+#    #+#             */
/*   Updated: 2021/03/12 22:02:39 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_main->term->c_lflag &= ~(ICANON|ECHOCTL);
	g_main->term->c_lflag |= (ECHOPRT);
	g_main->term->c_cc[VMIN] = 1;
	g_main->term->c_cc[VTIME] = 0;
	g_main->prompt = get_prompt(PROMPT, ft_strrchr(argv[0], '/') + 1);
	g_main->cmd_lines = NULL;
	get_term_info();
	debug_print_termios();
	debug_print_info_terminal();
}