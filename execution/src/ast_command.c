/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/29 15:21:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	make_input_redir(char **payload);
static int	make_output_redir(char **payload);
static t_log_chan	*make_input_heredoc(char **payload);
static t_com_redir make_redirection(char **payload);

/// @brief Make the input fd if payload contain at least one <.
/// @brief Also remove all data from payload about input redirection such as '<' and input file paths
/// @param payload Pointer to a command raw string (contain info about command, flags and redirection)
/// @return Input file descriptor
static int	make_input_redir(char **payload)
{
	int	input_fd;

	input_fd = -1;
	if (ft_strchr(*payload, '<'))
		input_fd = make_com_input(payload);
	return (input_fd);
}

/// @brief Make the output fd if payload contain at least one >.
/// @brief Also remove all data from payload about output redirection such as '>' and output file paths
/// @param payload Pointer to a command raw string (contain info about command, flags and redirection)
/// @return Output file descriptor
static int	make_output_redir(char **payload)
{
	int	output_fd;

	output_fd = -1;
	if (ft_strchr(*payload, '>'))
		output_fd = make_com_output(payload);
	return (output_fd);
}

static t_log_chan	*make_input_heredoc(char **payload)
{
	t_log_chan	*heredoc;

	heredoc = NULL;
	if (ftt_strnstr(*payload, "<<", ftt_strlen(*payload)))
		heredoc = make_heredoc(payload);
	return (heredoc);
}

static t_com_redir make_redirection(char **payload)
{
	t_com_redir	redirection;
	int			is_heredoc;
	int			is_input_file;
	int			is_output_file;

	redirection.status = 0;
	is_output_file = ft_strchr(*payload, '>') != NULL;
	is_heredoc = ftt_strnstr(*payload, "<<", ftt_strlen(*payload)) != NULL;
	redirection.output_file = make_output_redir(payload);
	redirection.status = is_output_file && redirection.output_file < 0;
	if (redirection.status != 0)
		return (redirection);
	redirection.heredoc = make_input_heredoc(payload);
	redirection.status = is_heredoc && redirection.heredoc == NULL;
	if (redirection.status != 0)
		return (redirection);
	is_input_file = ft_strchr(*payload, '<') != NULL;
	redirection.input_file = make_input_redir(payload);
	redirection.status = is_input_file && redirection.input_file < 0;
	if (redirection.status != 0)
		return (redirection);
	return (redirection);
}


int	make_q_command(t_com_queue *q, t_astnodes *node)
{
	t_com_node	*new_node;
	t_com_redir redir;
	char		*payload;
	
	payload = ft_substr(node->value, 0, ft_strlen(node->value));
	if (!payload)
		return (-1);
	if ((redir = make_redirection(&payload)).status != 0)
		return (free(payload), -1);
	// printf("'%s' is builtin : %d\n", payload, ft_checkcmd(payload));
	if (ft_checkcmd(payload) && !(new_node = add_builtin_node(q, payload)))
		return (free(payload), -1);
	if (!ft_checkcmd(payload) && !(new_node = add_node(q, payload)))
		return (free(payload), -1);
	if (redir.output_file != -1)
		new_node->out_file = redir.output_file;
	if (redir.input_file != -1)
		new_node->in_file = redir.input_file;
	if (redir.heredoc)
		new_node->heredoc = redir.heredoc;
	q->nodes = new_node;
	return (0);
}
