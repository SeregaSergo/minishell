/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:23:49 by bswag             #+#    #+#             */
/*   Updated: 2021/03/19 14:27:06 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_result_prev_cmd(int	res)
{
	g_main->i_result_prev_cmd = res;
	if (g_main->c_result_prev_cmd != NULL)
		free(g_main->c_result_prev_cmd);
	g_main->c_result_prev_cmd = ft_itoa(res);
}

t_env	*make_env_struct(char *env_elem)
{
	int		pos;
	t_env	*new;
	
	pos = ft_strchr_pos(env_elem, '=');
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		ft_error(ER_MEMORY);
	new->var = ft_substr(env_elem, 0, pos);
	new->cont = ft_substr(env_elem, pos + 1, ft_strlen(env_elem) - pos - 1);
	if (!new->var || !new->cont)
		ft_error(ER_MEMORY);
	return (new);
}

void	clone_envp(char **envp)
{
	int	len;
	int	i;

	i = 0;
	len = array_size((void **)envp);
	if (!(g_main->env = (t_env **)malloc(sizeof(t_env *) * (len + 1))))
		ft_error(ER_MEMORY);
	while (envp[i])
	{
		g_main->env[i] = make_env_struct(envp[i]);
		i++;
	}
	g_main->env[i] = NULL;
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
void	init_glob_struct(char **argv, char **envp)
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
	clone_envp(envp);
	get_term_info();
	retrieve_history(&g_main->history);
	g_main->cur_elem = g_main->history;
	g_main->cur_buf = NULL;
	g_main->n_symb_buf = 0;
	g_main->pos = 0;
	g_main->num_input_cmds = 0;
	g_main->c_result_prev_cmd = NULL;
	set_result_prev_cmd(0);
}