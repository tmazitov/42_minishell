/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/13 16:28:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	printer(t_com_node *command)
{
	int			counter;

	printf("%s\t| in : %p\t| out : %p\t| ", command->name, command->in_chan, command->out_chan);
	counter = 0;
	while (command->args[counter])
		printf("%s ", command->args[counter++]);
	printf("\t\n");
}

static void duper(t_com_node *command)
{
	t_log_chan	*input;
	t_log_chan	*output;

	input = command->in_chan;
	output = command->out_chan;
	if (input)
		dup2(input->side[0], STDIN_FILENO);
	if (output)
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
static void	command_proc(t_com_node *command, char **envp, t_com_queue *q)
{
	int			status;

	
	if (!command->path)
		panic(free_queue(q), 127);
	printer(command);
	duper(command);
	closer(command);
	status = execve(command->path, command->args, envp);
	free_queue(q);
	exit(status);
}

void	run_command_proc(t_com_node *command, char **envp, t_com_queue *q)
{
	pid_t	proc_id;

	if (!command || !envp)
		return ;
	proc_id = fork();
	if (proc_id == -1)
		return ;
	if (proc_id == 0)
		command_proc(command, envp, q);
	command->proc_id = proc_id;
	close_write(command->out_chan);
	close_read(command->in_chan);
}
