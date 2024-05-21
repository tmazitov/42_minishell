/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:41:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/11 09:50:28 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_com_node	*get_last(t_com_queue *q)
{
	t_com_node	*iter;

	if (!q || !q->nodes)
		return (NULL);
	iter = q->nodes;
	while (iter->next)
		iter = iter->next;
	return (iter);
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

t_com_node	*add_node(t_com_queue *q, char *command_line)
{
	t_com_node	*node;
	t_com_node	*last;

	node = make_node(command_line);
	if (!node)
		return (NULL);
	last = get_last(q);
	node->prev = last;
	if (last)
		last->next = node;
	return (node);
}

t_com_node	*get_node(t_com_queue *q)
{
	t_com_node
		*first;

	if (!q || !q->nodes)
		return (NULL);
	first = q->first;
	if (first)
		q->first = first->next;
	else
		q->first = get_first(q);
	return (first);
}

void	*free_queue_relationship(t_com_queue *q)
{
	t_com_node	*command;

	q->chan_closed = 1;
	command = get_first(q);
	while (command)
	{
		if (command->input)
			close_all_input(command->input);
		if (command->output)
			close_all_output(command->output);
		free_log_chan(command->in_chan);
		if (!command->next)
			break ;
		command = command->next;
	}
	if (command)
		free_log_chan(command->out_chan);
	return (NULL);
}
