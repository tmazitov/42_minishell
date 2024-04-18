/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/18 19:44:15 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/// @brief Make the input fd if payload contain at least one <.
/// @brief Also remove all data from payload about input redirection such as '<' and input file paths
/// @param payload Pointer to a command raw string (contain info about command, flags and redirection)
/// @return Input file descriptor
static int	make_input_redir(char **payload)
{
	int	input_fd;

	input_fd = -1;
	if (ft_strchr(*payload, '<'))
		input_fd = make_com_input(payload);
	return (input_fd);
}

/// @brief Make the output fd if payload contain at least one >.
/// @brief Also remove all data from payload about output redirection such as '>' and output file paths
/// @param payload Pointer to a command raw string (contain info about command, flags and redirection)
/// @return Output file descriptor
static int	make_output_redir(char **payload)
{
	int	output_fd;

	output_fd = -1;
	if (ft_strchr(*payload, '>'))
		output_fd = make_com_output(payload);
	return (output_fd);
}

int	make_q_command(t_com_queue *q, t_astnodes *node, char *path)
{
	t_com_node	*new_node;
	int			input_fd;
	int			output_fd;
	char		*command_payload;
	
	command_payload = ft_substr(node->value, 0, ft_strlen(node->value));
	if (!command_payload)
		return (-1);
	output_fd = make_output_redir(&command_payload);
	if (ft_strchr(command_payload, '>') && output_fd < 0)
		return (free(command_payload), -1);
	input_fd = make_input_redir(&command_payload);
	if (ft_strchr(command_payload, '<') && input_fd < 0)
		return (free(command_payload), -1);
	new_node = add_node(q, command_payload, path);
	if (!new_node)
		return (-1);
	if (output_fd != -1)
		new_node->out_file = output_fd;
	if (input_fd != -1)
		new_node->in_file = input_fd;
	q->nodes = new_node;
	return (0);
}
