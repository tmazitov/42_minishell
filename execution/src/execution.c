/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:27:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/27 19:57:57 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/// @brief Run executable commands one by one
/// @param commands Commands queue
/// @param envp Environment parameters
/// @return If each one command executed successfully return 0.
/// @return If create of child proccess in failed return -1.
static int	run_commands(t_com_queue *commands, t_envlist **envlist, t_varlist **varlist)
{
	t_com_node	*command;

	command = get_last(commands);
	while (command)
	{
		run_command_proc(command, envlist, varlist, commands);
		if (command->proc_id == -1)
			return (-1);
		command = command->prev;
	}
	return (0);
}
/// @brief Wait executable commands unt
/// @param commands Commands queue
/// @param count Length of the command queue
/// @return Status code of the last one executed command.
static int	wait_commands(t_com_queue *commands, int count)
{
	t_com_node	*command;
	int			counter;
	int			status;
	pid_t		pid;

	counter = 0;
	status = 0;
	while (counter < count)
	{
		pid = wait(&status);
		command = get_node_by_pid(commands, pid);
		if (command && !command->proc_status)
		{
			status = WEXITSTATUS(status);
			command->proc_status = status;
		}
		counter++;
	}
	command = get_last(commands);
	status = command->proc_status;
	return (status);
}


/// @brief Execute each one command from the AST tree
/// @param tree AST tree of commands 
/// @param envlist List of the environment parameters
/// @param varlist List of the variables
/// @return Status code of the last one executed command.
/// @return If tree is NULL or empty the status code will be -1.
int	execute(t_astnodes *tree, t_envlist **envlist, t_varlist **varlist)
{
	t_com_queue	*commands;
	int			status;
	int			command_count;

	if (!tree)
		return (-1);
	commands = make_ast_q(tree, envlist);
	if (!commands)
		return (-1);
	if (make_queue_relationship(commands) != 0)
		return (free_queue(commands), -1);
	if (run_commands(commands, envlist, varlist) != 0)
		return (free_queue(commands), -1);
	free_queue_relationship(commands);
	command_count = ast_tree_node_count(tree);
	status = wait_commands(commands, command_count);
	free_queue(commands);
	status_code(SET, status);
	return (status);
}



