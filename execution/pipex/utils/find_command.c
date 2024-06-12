/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:54:17 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/10 18:19:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../../../libft/get_next_line.h"

static char	*make_separator(void)
{
	char	*separator;

	separator = malloc(sizeof(char) * 2);
	if (!separator)
		return (NULL);
	separator[0] = '/';
	separator[1] = '\0';
	return (separator);
}

static char	*check_path(char *path, char *command_name)
{
	char	*directory;
	char	*command_path;
	char	*separator;
	int		ok;

	separator = make_separator();
	if (!separator)
		return (NULL);
	directory = ftt_strjoin(path, separator);
	if (!directory)
		return (free(separator), NULL);
	command_path = ftt_strjoin(directory, command_name);
	free(directory);
	free(separator);
	if (!command_path)
		return (NULL);
	ok = access(command_path, X_OK);
	if (ok == -1)
		return (free(command_path), NULL);
	return (command_path);
}

char	*find_command_path(char *command_name, char *env_path)
{
	char	**env_path_dirs;
	char	*result;
	int		counter;

	if (!env_path || !command_name)
		return (NULL);
	if (ft_strchr(command_name, '/'))
		return (command_name);
	counter = 0;
	env_path_dirs = ftt_split(env_path, ':');
	while (env_path_dirs[counter])
	{
		result = check_path(env_path_dirs[counter], command_name);
		if (result)
		{
			free_split(env_path_dirs);
			return (result);
		}
		counter++;
	}
	free_split(env_path_dirs);
	return (NULL);
}

char	*find_path(t_envlist **envlist)
{
	t_envlist	*env_node;

	if (!envlist)
		return (NULL);
	env_node = *envlist;
	while (env_node)
	{
		if (!ft_strncmp(env_node->varname, "PATH", 4))
			return (env_node->value);
		env_node = env_node->next;
	}
	return (NULL);
}
