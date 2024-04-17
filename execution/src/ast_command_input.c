/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:04:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/17 04:51:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

// int	add_com_input(t_com_node *node, char *input_path)
// {
// 	int input_fd;
	
// 	if (!node)
// 		return (-1);
// 	input_fd = open(input_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (input_fd <= 0)
// 		return (-1);
// 	if (!node->out_relay)
// 		node->out_relay = make_relay_chan(input_fd);
// 	else
// 		node->out_relay = relay_chan_add(node->out_relay, input_fd);
// 	if (!node->out_chan)
// 		return (-1);
// 	return (0);
// }