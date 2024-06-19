/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:30:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 21:19:55 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_free_env(t_envlist **envlist)
{
	t_envlist			*prev;

	while (*envlist != NULL)
	{
		free((*envlist)->value);
		free((*envlist)->varname);
		prev = *envlist;
		*envlist = (*envlist)->next;
		free(prev);
	}
}

int	cdcheck_path(char *path)
{
	int	exit_status;

	exit_status = 0;
	if (path == NULL)
		return (ft_err_b("bash: cd: OLDPWD not set\n", NULL, NULL), 1);
	if (ft_strlen(path) > NAME_MAX)
	{
		ft_err_b("bash: cd: ", path, ": File name too long\n");
		return (free(path), 1);
	}
	if (chdir(path) != 0)
	{
		ft_err_b("bash: cd: ", path, ": No such file or directory\n");
		return (free(path), 1);
	}
	return (exit_status);
}
