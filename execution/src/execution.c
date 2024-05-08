/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:27:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/08 16:58:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	run_infiles(t_com_queue *commands)
{
	t_com_node	*command;

	command = get_first(commands);
	while(command)
	{
		if (command->input && open_command_infile(command->input))
			return (1);
		command = command->next;
	}
	return (0);
}

static int	run_heredocs(t_com_queue *commands)
{
	t_com_node	*command;

	if (!commands)
		return (0);
	command = get_first(commands);
	while(command)
	{
		if (command->input && fill_command_heredoc(command->input))
			return (1);
		command = command->next;
	}
	return (0);
}

/// @brief Run executable commands one by one
/// @param commands Commands queue
/// @param envp Environment parameters
/// @return If each one command executed successfully return 0.
/// @return If create of child proccess in failed return -1.
static int	run_commands(t_com_queue *commands, t_envlist **envlist, t_varlist **varlist)
{
	t_com_node	*command;

	if (run_heredocs(commands))
		return (-1);
	status_code(SET, STOP_HEREDOC);
	if (run_infiles(commands))
		return (-1);
	command = get_last(commands);
	if (command && !command->prev && command->builtin)
		return (ft_builtins(command->builtin, envlist, varlist));
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
			if (status_code(GET, -1) != STOP_HEREDOC)
				status_code(SET, status);
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
	commands = make_ast_q(tree);
	if (status_code(GET, -1) == STOP_HEREDOC)
		status_code(SET, CTRL_C);
	if (!commands)
		return (-1);
	if (make_queue_relationship(commands) != 0)
		return (free_queue(commands), -1);
	command_count = ast_tree_node_count(tree);
	status_code(SET, IN_CMD);
	status = run_commands(commands, envlist, varlist);
	free_queue_relationship(commands);
	if (status != 0)
		return (free_queue(commands), -1);
	if (command_count == 1 && get_first(commands)->builtin)
		return (status_code(SET, 0));
	status = wait_commands(commands, command_count);
	free_queue(commands);
	return (status_code(SET, status));
}



