/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:16:31 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/04 15:56:25 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_com_queue	*make_queue(char **command_lines, int com_count)
{
	t_com_queue		*queue;
	t_com_node		*iter;
	int				counter;

	if (!command_lines || com_count == 0)
		return (NULL);
	queue = malloc(sizeof(t_com_queue));
	if (!queue)
		return (NULL);
	counter = 0;
	queue->nodes = NULL;
	iter = queue->nodes;
	while (command_lines[counter] && counter < com_count)
	{
		iter = add_node(queue, &command_lines[counter]);
		if (!iter)
			return (free_queue(queue));
		queue->nodes = iter;
		counter++;
	}
	if (make_queue_relationship(queue))
		return (free_queue(queue));
	queue->first = get_first(queue);
	queue->chan_closed = 0;
	return (queue);
}

int	make_queue_relationship(t_com_queue *queue)
{
	t_com_node		*command;
	t_log_chan		*chan;

	if (!queue)
		return (1);
	chan = NULL;
	command = get_first(queue);
	if (!command || (!command->next && !command->prev))
		return (0);
	while (command)
	{
		if (command->prev)
			command->in_chan = chan;
		chan = make_log_chan();
		if (!chan)
			return (1);
		if (!command->next)
		{
			free_log_chan(chan);
			break ;
		}
		command->out_chan = chan;
		command = command->next;
	}
	return (0);
}
