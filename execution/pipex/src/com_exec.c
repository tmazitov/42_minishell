/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/27 20:55:39 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	printer(t_com_node *command)
{
	if (command->builtin)
		printf("B-IN\t| %s\t", command->builtin);
	else
		printf("CMD\t| %s\t", command->name);
	printf("| pipe-in : %p\t| pipe-out : %p\t", command->in_chan, command->out_chan);
	printf("| file-in : %d\t| file-out : %d\t", command->in_file, command->out_file);
	printf("| heredoc : %p\t|", command->heredoc);
	printf("\n");
}

static void duper(t_com_node *command)
{
	t_log_chan	*input;
	t_log_chan	*output;

	input = command->in_chan;
	output = command->out_chan;
	if (command->heredoc)
		dup2(command->heredoc->side[0], STDIN_FILENO);
	else if (command->in_file != -1)
		dup2(command->in_file, STDIN_FILENO);
	else if (input && input->side[0] != -1)
		dup2(input->side[0], STDIN_FILENO);
	if (command->out_file != -1)
		dup2(command->out_file, STDOUT_FILENO);
	else if (output && output->side[1] != -1)
		dup2(output->side[1], STDOUT_FILENO);
}

static void	closer(t_com_node *command)
{
	if (command->in_chan)
	{
		close_read(command->in_chan);
		close_write(command->in_chan);
	}
	if (command->out_chan)
	{
		close_write(command->out_chan);
		close_read(command->out_chan);
	}
}

static void	command_proc(t_com_node *command, t_envlist **envlist, t_varlist **varlist, t_com_queue *q)
{
	int			status;
	char		**envp;
	
	if (!command->path && !command->builtin)
	{
		free_queue(q);
		free_envlist(*envlist);
		panic(NULL, 127);
	}
	printer(command);
	duper(command);
	closer(command);
	status = 0;
	if (command->path)
	{
		// printf("command path : %s\n", command->path);
		envp = ft_env_converter(envlist);
		if (!envp)
		{
			free_envlist(*envlist);
			free_queue(q);
			exit(1);
		}
		status = execve(command->path, command->args, envp);
		free_split(envp);
	}
	else if (command->builtin)
		status = ft_builtins(command->builtin, envlist, varlist);
	free_envlist(*envlist);
	free_queue(q);
	exit(status);
}

void	run_command_proc(t_com_node *command, t_envlist **envlist, t_varlist **varlist, t_com_queue *q)
{
	pid_t	proc_id;

	if (!command || !envlist)
		return ;
	proc_id = fork();
	if (proc_id == -1)
		return ;
	if (proc_id == 0)
		command_proc(command, envlist, varlist, q);
	command->proc_id = proc_id;
	close_write(command->out_chan);
	close_read(command->in_chan);
}
