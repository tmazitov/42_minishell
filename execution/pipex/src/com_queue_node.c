/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:47 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 22:29:50 by emaravil         ###   ########.fr       */
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

static int	init_redirection(t_com_node *node, char **input)
{
	char	**t;
	int		ctn;

	t = ft_splittoken(*input);
	if (!t)
		return (0);
	ctn = -1;
	while (t[++ctn])
	{
		if (!node->input && \
			(!ft_strncmp(t[ctn], "<", 2) || !ft_strncmp(t[ctn], "<<", 3)))
		{
			node->input = make_input_storage(input);
			if (!node->input)
				return (free_pointer(t), 0);
		}
		if (!node->output && \
			(!ft_strncmp(t[ctn], ">", 2) || !ft_strncmp(t[ctn], ">>", 3)))
		{
			node->output = make_output_storage(input);
			if (!node->output)
				return (free_pointer(t), 0);
		}
	}
	return (free_pointer(t), 1);
}

t_com_node	*make_node(char **com)
{
	t_com_node	*node;

	if (!com || !*com)
		return (NULL);
	node = malloc(sizeof(t_com_node));
	if (!node)
		return (NULL);
	init_node(node);
	if (!init_redirection(node, com))
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
