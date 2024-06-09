/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:50:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 02:26:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../parsing/includes/parse.h"
# include "../pipex/src/pipex.h"
# include "../signals/includes/signals.h"

typedef struct s_com_redir
{
	int			input_file;
	int			output_file;
	t_log_chan	*heredoc;
	int			status;
}		t_com_redir;

// AST to the command queue

int			make_q_command(t_com_queue *q, t_astnodes *node);
t_com_queue	*make_ast_q(t_astnodes **tree);
int			ast_q_add_command(t_com_queue *q, t_astnodes *node);
int			ast_tree_node_count(t_astnodes *node);
t_com_node	*add_builtin_node(t_com_queue *q, char **command_line);

// Execution functions

int			execute(t_astnodes **tree, t_envlist **envlist, \
			t_varlist **varlist);
int			single_builtin(t_com_node *command, t_builtin_info *info);

// Utils
int			ast_q_length(t_com_queue *q);
int			run_infiles(t_com_queue *commands);
int			run_heredocs(t_com_queue *commands, t_envlist **env, \
			t_varlist **var);
void		ft_free_ast(t_astnodes *root);
void		ft_free_ast_temp(t_astnodes *rootnode);
char		*filter_spaces(char *str);

#endif // !EXECUTION_H