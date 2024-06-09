/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:52:25 by tmazitov          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/09 01:29:33 by emaravil         ###   ########.fr       */
=======
/*   Updated: 2024/06/09 02:27:41 by tmazitov         ###   ########.fr       */
>>>>>>> 76995f6f30c16213484b53ae881eb1d190d565fd
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/// @brief Make executable commands by AST tree
/// @param tree AST tree of commands 
/// @param envlist List of the environment params
/// @return List of the executable commands
/// @return Return NULL if the PATH not exists
/// @return Return NULL if not enough memory
/// @return Return NULL if tree is empty
t_com_queue	*make_ast_q(t_astnodes **tree)
{
	t_com_queue			*commands;

	commands = malloc(sizeof(t_com_queue));
	if (!commands)
		return (NULL);
	commands->chan_closed = 0;
	commands->nodes = NULL;
	commands->first = NULL;
	if (ast_q_add_command(commands, *tree) != 0)
		return (free_queue(commands));
	ft_free_ast(*tree);
	*tree = NULL;
	return (commands);
}

int	ast_q_add_command(t_com_queue *q, t_astnodes *node)
{
	if (node->left && ast_q_add_command(q, node->left) != 0)
		return (1);
	if (node->right && ast_q_add_command(q, node->right) != 0)
		return (1);
	if (!node->right && !node->left)
		return (make_q_command(q, node));
	return (0);
}

int	ast_q_length(t_com_queue *q)
{
	t_com_node	*node;
	int			length;

	if (!q || !q->nodes)
		return (0);
	node = get_first(q);
	length = 0;
<<<<<<< HEAD
	while (node)
=======
	while (node) 
>>>>>>> 76995f6f30c16213484b53ae881eb1d190d565fd
	{
		if (node->name)
			length++;
		node = node->next;
	}
	return (length);
}

int	ast_tree_node_count(t_astnodes *node)
{
	int	count;

	if (!node)
		return (0);
	count = 0;
	count += ast_tree_node_count(node->left);
	count += ast_tree_node_count(node->right);
	if (!node->left && !node->right)
		count += 1;
	return (count);
}
