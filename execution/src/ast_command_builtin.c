/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:33:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/27 19:55:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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
	node->builtin = NULL;
	node->name = NULL;
	node->path = NULL;
	node->builtin = NULL;
	node->args = NULL;
}

t_com_node	*make_builtin_node(char *command_line)
{
	t_com_node	*node;

	if (!command_line)
		return (NULL);
	printf("built in node : '%s' \n", command_line);
	node = malloc(sizeof(t_com_node));
	if (!node)
		return (NULL);
	init_node(node);
	node->builtin = command_line;
	return (node);
}

t_com_node	*add_builtin_node(t_com_queue *q, char *command_line)
{
	t_com_node	*node;
	t_com_node	*last;

	node = make_builtin_node(command_line);
	if (!node)
		return (NULL);
	last = get_last(q);
	node->prev = last;
	if (last)
		last->next = node;
	return (node);
}