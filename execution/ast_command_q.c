/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:52:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/11 16:09:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


/// @brief Make executable commands by AST tree
/// @param tree AST tree of commands 
/// @param envp Environment params
/// @return List of the executable commands
/// @return Return NULL if the PATH not exists
/// @return Return NULL if not enough memory
/// @return Return NULL if tree is empty
t_com_queue	*make_ast_q(t_astnodes *tree, char **envp)
{
	t_com_queue			*commands;
	int					count;
	char				*path;

	path = find_path(envp);
	if (!path)
		return (NULL);
	commands = malloc(sizeof(t_com_queue));
	if (!commands)
		return (NULL);
	commands->chan_closed = 0;
	commands->nodes = NULL;
	commands->first = NULL;
	if (ast_q_add_command(commands, tree, path) != 0)
		return (free_queue(commands));
	return (commands);
}

int	ast_q_add_command(t_com_queue *q, t_astnodes *node, char *path)
{
	int			status;
	t_com_node	*new_node;

	if (node->left)
		status = ast_q_add_command(q, node->left, path);
	if (status != 0)
		return (-1);
	if (node->right)
		status = ast_q_add_command(q, node->right, path);
	if (status != 0)
		return (-1);
	if (!node->right && !node->left)
	{
		new_node = add_node(q, node->value, path);
		if (!new_node)
			return (-1);
	}
	return (0);
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