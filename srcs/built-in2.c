/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 01:20:56 by bswag             #+#    #+#             */
/*   Updated: 2021/05/16 01:27:47 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value_env(char *new, char **value)
{
	if (!ft_strcmp(*value, new))
		return (0);
	free(*value);
	*value = new;
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3))
		return (0);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (0);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (0);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (0);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (0);
	else if (!ft_strncmp(cmd, "export", 7))
		return (0);
	else if (!ft_strncmp(cmd, "env", 4))
		return (0);
	return (1);
}

void	exec_in_the_same_proc(t_cmd *cmd)
{
	int	stdin;
	int	stdout;

	stdin = dup(0);
	stdout = dup(1);
	redirect_streams(cmd);
	set_result_prev_cmd(execute_cmd(cmd));
	dup2(stdin, 0);
	dup2(stdout, 1);
}
