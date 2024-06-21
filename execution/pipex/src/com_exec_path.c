/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:16:43 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 22:29:14 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_absolute_path(char *path)
{
	int	ok;

	ok = access(path, X_OK);
	if (ok == -1)
		return (NULL);
	return (path);
}

char	*command_path(t_com_node *command, t_envlist **envlist)
{
	char	*path;

	if (!command || !envlist)
		return (NULL);
	path = find_path(envlist);
	if (ft_strnstr(command->name, "./", 3))
		command->path = check_absolute_path(command->name);
	else if (!path)
		return (NULL);
	else
		command->path = find_command_path(command->name, path);
	return (command->path);
}
