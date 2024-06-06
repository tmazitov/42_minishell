/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:00:36 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/06 17:01:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int	run_infiles(t_com_queue *commands)
{
	t_com_node	*command;
	int			status;

	command = get_first(commands);
	while(command)
	{
		if (command->input 
			&& (status = open_command_infile(command->input)))
			return (1);
		command = command->next;
	}
	return (0);
}

int	run_heredocs(t_com_queue *commands)
{
	t_com_node	*command;
	int			status;

	if (!commands)
		return (0);
	command = get_first(commands);
	while(command)
	{
		if (command->input 
			&& (status = fill_command_heredoc(command->input)))
			return (status);
		command = command->next;
	}
	return (0);
}