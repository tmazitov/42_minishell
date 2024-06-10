/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:16:43 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/10 16:30:40 by tmazitov         ###   ########.fr       */
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
	char	*current_path;

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
