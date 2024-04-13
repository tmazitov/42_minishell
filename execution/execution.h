/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:50:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/13 18:05:43 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/includes/parse.h"
# include "./pipex/src/pipex.h"

// AST to the command queue

t_com_queue	*make_ast_q(t_astnodes *tree, char **envp);
int			ast_q_add_command(t_com_queue *q, t_astnodes *node, char *path);
int			ast_tree_node_count(t_astnodes *node);

// Execution functions

int	execute(t_astnodes *tree, char **envp);

// Redirection relay

t_log_chan	*make_relay_chan(int fd);
t_log_chan	*relay_chan_add(t_log_chan *chan, int fd);

int			add_com_output(t_com_node *node, char *output_path);

#endif // !EXECUTION_H