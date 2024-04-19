/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_q.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:52:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/18 17:52:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"


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

	if (node->left && ast_q_add_command(q, node->left, path) != 0)
		return (-1);
	if (node->right && ast_q_add_command(q, node->right, path) != 0)
		return (-1);
	if (!node->right && !node->left)
		return (make_q_command(q, node, path));
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