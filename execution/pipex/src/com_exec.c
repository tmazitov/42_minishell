/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/03 15:38:04 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	printer(t_com_node *command)
// {
// 	if (command->builtin)
// 		printf("B-IN\t| %s\t", command->builtin);
// 	else
// 		printf("CMD\t| %s\t", command->name);
// 	printf("| pipe-in : %p\t| pipe-out : %p\t", command->in_chan, command->out_chan);
// 	printf("| file-in : %d\t| file-out : %d\t", command->in_file, command->out_file);
// 	printf("| heredoc : %p\t|", command->heredoc);
// 	printf("\n");
// }

static void duper(t_com_node *command)
{
	t_log_chan	*pipe_input;
	t_log_chan	*pipe_output;

	pipe_input = command->in_chan;
	pipe_output = command->out_chan;
	if (command->input && get_last_input(command->input))
		dup2(get_last_input(command->input)->fd, STDIN_FILENO);
	else if (pipe_input && pipe_input->side[0] != -1)
		dup2(pipe_input->side[0], STDIN_FILENO);
	if (command->output && get_last_output(command->output))
		dup2(get_last_output(command->output)->fd, STDOUT_FILENO);
	else if (pipe_output && pipe_output->side[1] != -1)
		dup2(pipe_output->side[1], STDOUT_FILENO);
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
	t_log_chan	*heredoc;

	if (command->name && !command->builtin)
		command_path(command, envlist);
	if (!command->path && !command->builtin)
	{
		free_queue(q);
		ft_free_env(envlist);
		ft_free_var(varlist);
		exit(127);
	}
	duper(command);
	closer(command);
	status = 0;
	if (command->path)
	{
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

int	run_command_proc(t_com_node *command, t_envlist **envlist, t_varlist **varlist, t_com_queue *q)
{
	pid_t	proc_id;

	if (!command || !envlist)
		return (1);
	proc_id = fork();
	if (proc_id == -1)
		return (1);
	if (proc_id == 0)
		command_proc(command, envlist, varlist, q);
	command->proc_id = proc_id;
	close_write(command->out_chan);
	close_read(command->in_chan);
	return (0);
}
