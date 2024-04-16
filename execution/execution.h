/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:50:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/16 19:43:50 by tmazitov         ###   ########.fr       */
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

int			execute(t_astnodes *tree, char **envp);

// Command io redirection

int			make_com_output(char **com_payload);

// Utils

char		*filter_spaces(char *str);

#endif // !EXECUTION_H