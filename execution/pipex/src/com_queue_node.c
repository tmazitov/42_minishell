/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:47 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/04 15:53:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_node(t_com_node *node)
{
	node->next = NULL;
	node->prev = NULL;
	node->in_chan = NULL;
	node->out_chan = NULL;
	node->proc_id = -1;
	node->proc_status = 0;
	node->output = NULL;
	node->input = NULL;
	node->builtin = NULL;
	node->name = NULL;
	node->path = NULL;
	node->builtin = NULL;
	node->args = NULL;
}

t_com_node	*make_node(char **com)
{
	t_com_node	*node;
	char		**command_parts;

	if (!com || !*com)
		return (NULL);
	node = malloc(sizeof(t_com_node));
	if (!node)
		return (NULL);
	init_node(node);
	if (ft_strchr(*com, '<') && !(node->input = make_input_storage(com)))
		return (free_node(node));
	if (ft_strchr(*com, '>') && !(node->output = make_output_storage(com)))
		return (free_node(node));
	node->args = ftt_split(*com, ' ');
	if (!node->args)
		return (free_node(node));
	node->name = node->args[0];
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
	if (node->path)
		free(node->path);
	if (node->builtin)
		free(node->builtin);
	if (node->args)
		free_split(node->args);
	if (node->input)
		free_input_storage(node->input);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	return (NULL);
}
