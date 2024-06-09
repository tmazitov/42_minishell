/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:33:56 by tmazitov          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/08 22:05:52 by emaravil         ###   ########.fr       */
=======
/*   Updated: 2024/06/09 02:26:44 by tmazitov         ###   ########.fr       */
>>>>>>> 76995f6f30c16213484b53ae881eb1d190d565fd
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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

t_com_node	*make_builtin_node(char **com)
{
	t_com_node	*node;

	if (!com || !*com)
		return (NULL);
	node = malloc(sizeof(t_com_node));
	if (!node)
		return (NULL);
	init_node(node);
	if (ft_strchr(*com, '<'))
		node->input = make_input_storage(com);
	if (ft_strchr(*com, '<') && !node->input)
		return (free_node(node));
	if (ft_strchr(*com, '>'))
		node->output = make_output_storage(com);
	if (ft_strchr(*com, '>') && !node->output)
		return (free_node(node));
	node->builtin = ft_substr(*com, 0, ft_strlen(*com));
	if (!node->builtin)
		return (free_node(node));
	return (node);
}

t_com_node	*add_builtin_node(t_com_queue *q, char **command_line)
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

int	single_builtin(t_com_node *command, t_builtin_info *info)
{
	int	status;
	int	temp_in;
	int	temp_out;

	temp_in = 0;
	temp_out = 0;
	if (command->input && get_last_input(command->input))
		dup2(get_last_input(command->input)->fd, STDIN_FILENO);
	if (command->output && get_last_output(command->output))
		dup2(get_last_output(command->output)->fd, STDOUT_FILENO);
	status = ft_builtins(command->builtin, info);
	if (command->input && get_last_input(command->input))
		dup2(temp_in, STDIN_FILENO);
	if (command->output && get_last_output(command->output))
		dup2(temp_out, STDOUT_FILENO);
	return (status);
}
