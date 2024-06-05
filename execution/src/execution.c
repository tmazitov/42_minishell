/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:27:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/05 19:59:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	run_infiles(t_com_queue *commands)
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

static int	run_heredocs(t_com_queue *commands)
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

/// @brief Run executable commands one by one
/// @param commands Commands queue
/// @param envp Environment parameters
/// @return If each one command executed successfully return 0.
/// @return If create of child proccess in failed return -1.
static int	run_commands(t_com_queue *commands, t_envlist **envlist, t_varlist **varlist)
{
	t_com_node		*command;
	int				status;
	t_builtin_info	info;

	if ((status = run_heredocs(commands))) 
		return (status);
	status_code(SET, STOP_HEREDOC);
	if ((status = run_infiles(commands)))
		return (status);
	info.env = envlist;
	info.var = varlist;
	info.q = commands;
	command = get_first(commands);
	if (command && !command->next && command->builtin)
		return (single_builtin(command, &info));
	while (command)
	{
		if (command->name && 
			(status = run_command_proc(command, &info)))
			return (status);
		command = command->next;
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
		if (command && WIFEXITED(status))
		{
			printf("\traw : %d\n", status);
			status = WEXITSTATUS(status);
			printf("\there status : %d\n", status);
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
int	execute(t_astnodes **tree, t_envlist **envlist, t_varlist **varlist)
{
	t_com_queue	*commands;
	int			command_count;

	if (!tree || !*tree)
		return (status_code(SET, 1));
	if (!(commands = make_ast_q(*tree)))
		return (status_code(SET, 1));
	if (make_queue_relationship(commands) != 0)
		return (free_queue(commands), status_code(SET, 1));
	command_count = ast_tree_node_count(*tree);
	ft_free_ast(*tree);
	*tree = NULL;
	printf("status code : %d\n", status_code(GET, -1));
	status_code(SET, IN_CMD);
	if (status_code(SET, run_commands(commands, envlist, varlist)))
	{
		if (status_code(GET, -1) == 2)
			status_code(SET, 0);
		return (free_queue(commands), 0);
	}
	free_queue_relationship(commands);
	if (command_count == 1 && get_first(commands)->builtin)
		return (free_queue(commands), 0);
	status_code(SET, wait_commands(commands, command_count));
	printf("status code : %d\n", status_code(GET, -1));
	free_queue(commands);
	return (0);
}
