/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:50:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/27 18:59:37 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../parsing/includes/parse.h"
# include "../pipex/src/pipex.h"
# include "../signals/includes/signals.h"
# include "../../builtins/builtins.h"

typedef	struct s_com_redir
{
	int			input_file;
	int			output_file;
	t_log_chan	*heredoc;
	int			status;
}		t_com_redir;



// AST to the command queue

int			make_q_command(t_com_queue *q, t_astnodes *node, char *path);
t_com_queue	*make_ast_q(t_astnodes *tree, t_envlist **envlist);
int			ast_q_add_command(t_com_queue *q, t_astnodes *node, char *path);
int			ast_tree_node_count(t_astnodes *node);
t_com_node	*add_builtin_node(t_com_queue *q, char *command_line);

// Execution functions

int			execute(t_astnodes *tree, t_envlist **envlist, t_varlist **varlist);

// Command io redirection

int			make_com_output(char **com_payload);
int			make_com_input(char **com_payload);
t_log_chan 	*make_heredoc(char **com_payload);

// Utils

char		*filter_spaces(char *str);

// Heredoc

t_log_chan *make_heredoc(char **com_payload);
#endif // !EXECUTION_H