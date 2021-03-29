#include <__wctype.h>
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egilbert <egilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:33:16 by egilbert          #+#    #+#             */
/*   Updated: 2021/03/02 19:32:07 by egilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*new_value(char *key, char *value)
{
	char *new;
	int k_len;

	k_len = ft_strlen(key);
	new = (char *)malloc(ft_strlen(key) + ft_strlen(value) + 2);
	ft_strlcpy(new, key, k_len + 1);
	new[k_len] = '=';
	ft_strlcpy(&new[k_len + 1], value, ft_strlen(value) + 1);
	return (new);
}

void	change_env_value(t_shell *bash, char *key, char *value)
{
	int i;
	int k_len;

	k_len = ft_strlen(key);
	i = -1;
	while (bash->env[++i] != NULL)
    {
		if (!ft_strncmp(bash->env[i], key, k_len) && bash->env[i][k_len] == '=')
		{
			free(bash->env[i]);
			bash->env[i] = new_value(key, value);
		}
	}

}


void	cd(char *path, t_shell *bash)
{
    char *old;

    old = getcwd(NULL, 1);
	if (!chdir(path))
	{
	    change_env_value(bash, "OLDPWD", old);
		change_env_value(bash, "PWD", getcwd(NULL, 1));
	    free(old);
		return ;
	}
    free(old);
	perror("cd");
}
