/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:25:10 by bswag             #+#    #+#             */
/*   Updated: 2021/03/04 23:06:09 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	int		res;
	char	*buf;
	// t_exec	*exec_struct;
	
	switch_off_signals();
	g_prompt = find_envp("USER=", envp, &argv[0][2]);
	if (argc != 1)
		ft_error(ER_ARGS);
	while (1)
	{
		ft_printf("%s%% ", g_prompt);
		buf = NULL;
		res = get_next_line(0, &buf);
		if (res <= 0 && buf[0] == '\0')
		{
			ft_printf("\n");
			exit(0);
		}
		// exec_struct = parse_input(buf);
		free(buf);
		// execute_comands(exec_struct);
		// clear_struct(exec_struct);
		ft_printf("%s\n", buf);
	}
	return (0);
}
