/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:25:57 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/20 17:48:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	*free_split(char **split_result)
{
	int	counter;

	counter = 0;
	while (split_result[counter])
		free(split_result[counter++]);
	free(split_result);
	return (NULL);
}

static void	*free_node(t_com_node *node)
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
	if (node->output)
		free_output_storage(node->output);
	if (node->in_chan)
		free_log_chan(node->in_chan);
	if (node->out_chan)
		free_log_chan(node->out_chan);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	return (NULL);
}

t_com_node	*get_first(t_com_queue *q)
{
	t_com_node	*iter;

	if (!q || !q->nodes)
		return (NULL);
	iter = q->nodes;
	while (iter->prev)
		iter = iter->prev;
	return (iter);
}

void	*free_queue_relationship(t_com_queue *q)
{
	t_com_node	*command;

	if (q->chan_closed == 1)
		return (NULL);
	q->chan_closed = 1;
	command = get_first(q);
	while (command)
	{
		if (command->next && command->out_chan)
			command->out_chan = NULL;
		if (command->input)
			command->input = free_input_storage(command->input);
		if (command->output)
			command->output = free_output_storage(command->output);
		if (command->in_chan)
			command->in_chan = free_log_chan(command->in_chan);
		if (!command->next)
			break ;
		command = command->next;
	}
	return (NULL);
}

void	*free_queue(t_com_queue *q)
{
	t_com_node	*first;
	t_com_node	*iter;

	if (!q)
		return (NULL);
	if (!q->chan_closed)
		free_queue_relationship(q);
	first = get_first(q);
	iter = first;
	while (first)
	{
		iter = first->next;
		free_node(first);
		first = iter;
	}
	free(q);
	return (NULL);
}
