/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/11 13:21:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	make_q_command(t_com_queue *q, t_astnodes *node)
{
	t_com_node	*new_node;
	char		*payload;

	payload = ft_substr(node->value, 0, ft_strlen(node->value));
	if (!payload)
		return (-1);
	new_node = NULL;
	if (ft_checkcmd(payload))
		new_node = add_builtin_node(q, payload);
	else if (ft_strchr(payload, '=') && !ft_checkcmd(payload))
		new_node = add_builtin_node(q, payload);
	else 
		new_node = add_node(q, payload);
	if (!new_node)
		return (-1);
	q->nodes = new_node;
	return (0);
}
