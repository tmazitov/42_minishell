/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:42:39 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/13 18:24:52 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	add_com_output(t_com_node *node, char *output_path)
{
	int output_fd;
	
	if (!node)
		return (-1);
	output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_fd <= 0)
		return (-1);
	if (!node->out_relay)
		node->out_relay = make_relay_chan(output_fd);
	else
		node->out_relay = relay_chan_add(node->out_relay, output_fd);
	if (!node->out_relay)
		return (-1);
	return (0);
}