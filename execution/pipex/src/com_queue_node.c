/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:47 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/19 15:36:05 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_node(t_com_node *node)
{
	node->next = NULL;
	node->prev = NULL;
	node->in_chan = NULL;
	node->out_chan = NULL;
	node->out_file = -1;
	node->in_file = -1;
	node->proc_id = -1;
	node->proc_status = 0;
	node->heredoc = NULL;
}

t_com_node	*make_node(char *command_line, char *env_path)
{
	t_com_node	*node;
	char		**command_parts;

	if (!command_line)
		return (NULL);
	node = malloc(sizeof(t_com_node));
	if (!node)
		return (NULL);
	init_node(node);
	command_parts = ftt_split(command_line, ' ');
	if (!command_parts)
	{
		free_node(node);
		return (NULL);
	}
	node->name = command_parts[0];
	node->args = command_parts;
	node->path = find_command_path(command_parts[0], env_path);
	return (node);
}

t_com_node	*get_node_by_pid(t_com_queue *q, pid_t pid)
{
	t_com_node	*command;

	command = get_first(q);
	while (command)
	{
		if (command->proc_id == pid)
			return (command);
		command = command->next;
	}
	return (NULL);
}

void	*free_node(t_com_node *node)
{
	if (!node)
		return (NULL);
	if (!ft_strchr(node->name, '/') && node->path)
		free(node->path);
	if (node->args)
		free_split(node->args);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	return (NULL);
}
