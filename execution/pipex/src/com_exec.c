/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 14:30:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	panic(t_com_node *com, t_builtin_info *info, int status)
{
	if (status == 127)
	{
		write(2, "minishell: ", 12);
		write(2, com->name, ft_strlen(com->name));
		write(2, ": command not found\n", 21);
	}
	free_queue(info->q);
	ft_free_env(info->env);
	ft_free_var(info->var);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}

static void	duper(t_com_node *command)
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

static void	command_proc(t_com_node *command, t_builtin_info *info)
{
	int			status;
	char		**envp;
	t_log_chan	*heredoc;

	if (command->name && !command->builtin)
		command_path(command, info->env);
	if (!command->path && !command->builtin)
		panic(command, info, 127);
	duper(command);
	free_queue_relationship(info->q);
	status = 0;
	if (command->builtin)
		panic(command, info, ft_builtins(command->builtin, info));
	envp = ft_env_converter(info->env);
	if (!envp)
		panic(command, info, 1);
	status = execve(command->path, command->args, envp);
	free_split(envp);
	panic(command, info, status);
}

int	run_command_proc(t_com_node *command, t_builtin_info *info)
{
	pid_t	proc_id;

	if (!info->env || !info->var || !info->q)
		return (1);
	proc_id = fork();
	if (proc_id == -1)
		return (1);
	if (proc_id == 0)
		command_proc(command, info);
	command->proc_id = proc_id;
	close_write(command->out_chan);
	close_read(command->in_chan);
	return (0);
}
