/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:55:50 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/13 14:58:40 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	*free_envlist(t_envlist *envlist)
{
	if (envlist->next)
		free_envlist(envlist->next);
	free(envlist->value);
	free(envlist->varname);
	return (NULL);
}

char	**ft_env_converter(t_envlist **envlist)
{
	char		**converted;
	int			length;
	t_envlist	*node;

	if (!envlist)
		return (NULL);
	length = 0;
	node = *envlist;
	while (node)
	{
		length++;
		node = node->next;
	}
	converted = malloc(sizeof(char *) * (length + 1));
	if (!converted)
		return (NULL);
	node = *envlist;
	length = 0;
	converted = ft_env_converter_b(converted, node);
	return (converted);
}

char	**ft_env_converter_b(char **converted, t_envlist *node)
{
	int	length;

	length = 0;
	while (node)
	{
		converted[length] = ft_env_to_string(node);
		if (!converted[length])
			return (NULL);
		length++;
		node = node->next;
	}
	converted[length] = NULL;
	return (converted);
}
