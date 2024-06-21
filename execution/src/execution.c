/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:27:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 19:55:39 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	run_prep(t_com_queue *commands, t_envlist **envlist, \
	t_varlist **varlist)
{
	int	status;

	status = run_heredocs(commands, envlist, varlist);
	if (status)
		return (status);
	status_code(SET, STOP_HEREDOC);
	run_infiles(commands);
	return (0);
}

/// @brief Run executable commands one by one
/// @param commands Commands queue
/// @param envp Environment parameters
/// @return If each one command executed successfully return 0.
/// @return If create of child proccess in failed return -1.
static int	run_commands(t_com_queue *commands, t_envlist **envlist, \
	t_varlist **varlist)
{
	t_com_node		*command;
	int				status;
	t_builtin_info	info;

	status = run_prep(commands, envlist, varlist);
	if (status)
		return (status);
	status_code(SET, IN_CMD);
	info.env = envlist;
	info.var = varlist;
	info.q = commands;
	command = get_first(commands);
	if (command && !command->next && command->builtin)
		return (single_builtin(command, &info));
	while (command)
	{
		if (command->name || command->builtin)
			status = run_command_proc(command, &info);
		if (status)
			return (status);
		command = command->next;
	}
	return (0);
}

/// @brief Wait executable commands unt
/// @param commands Commands queue
/// @param count Length of the command queue
/// @return Status code of the last one executed command.
static int	wait_commands(t_com_queue *commands)
{
	t_com_node	*command;
	int			counter;
	int			count;
	int			status;
	pid_t		pid;

	counter = 0;
	count = ast_q_length(commands);
	status = 0;
	while (counter < count)
	{
		pid = wait(&status);
		command = get_node_by_pid(commands, pid);
		if (command && status_code(GET, -1) != IN_CMD)
		{
			command->proc_status = status_code(GET, -1);
			status_code(SET, IN_CMD);
		}
		else if (command && WIFEXITED(status))
			command->proc_status = WEXITSTATUS(status);
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
int	execute(t_astnodes **tree, t_envlist **envlist, t_varlist **varlist)
{
	t_com_queue	*commands;
	int			status;

	if (!tree || !*tree)
		return (status_code(SET, 1));
	commands = make_ast_q(tree);
	if (!commands)
		return (status_code(SET, 1));
	if (make_queue_relationship(commands) != 0)
		return (free_queue(commands), status_code(SET, 1));
	status = run_commands(commands, envlist, varlist);
	if (status)
	{
		if (status_code(SET, status) == 2)
			status_code(SET, 0);
		return (free_queue(commands), 0);
	}
	free_queue_relationship(commands);
	if (ast_q_length(commands) == 1 && get_first(commands)->builtin)
		return (free_queue(commands), status_code(SET, 0));
	status_code(SET, wait_commands(commands));
	free_queue(commands);
	return (0);
}
