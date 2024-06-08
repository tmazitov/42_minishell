/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:54:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/08 15:59:12 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../chan/chan.h"
# include "../utils/utils.h"
# include "../../../libft/get_next_line.h"
# include "../../../libft/ft_printf.h"
# include "input/input.h"
# include "output/output.h"

// QUEUE NODE
t_com_node	*make_node(char **command_line);
void		*free_node(t_com_node *node);
char		*command_path(t_com_node *command, t_envlist **envlist);

// QUEUE
int			make_queue_relationship(t_com_queue *queue);
t_com_queue	*make_queue(char **command_lines, int com_count);
t_com_node	*get_node(t_com_queue *queue);
t_com_node	*add_node(t_com_queue *queue, char **command_line);
t_com_node	*get_last(t_com_queue *queue);

t_com_node	*get_node_by_pid(t_com_queue *queue, pid_t pid);

// MULTIPROCCESSING
int			run_command_proc(t_com_node *command, t_builtin_info *info);
// INPUT FILE
// int			add_input(t_com_queue *queue, char *input_path);
// int			check_input(char *input_path);
// t_log_chan	*make_input(char *input_path);

// OUTPUT FILE
// int			add_output(t_com_queue *queue, char *output_path);
// t_log_chan	*make_output(char *output_path);

// HEREDOC
// t_log_ chan	*make_heredoc(char **com_payload);

#endif
