/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:50:56 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/19 15:47:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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
	if (ft_strnstr(*payload, "<<", ft_strlen(*payload)))
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
	is_heredoc = ft_strnstr(*payload, "<<", ft_strlen(*payload)) != NULL;
	redirection.output_file = make_output_redir(payload);
	redirection.status = is_output_file && redirection.output_file < 0;
	if (redirection.status != 0)
		return (free(*payload), redirection);
	redirection.heredoc = make_input_heredoc(payload);
	redirection.status = is_heredoc && redirection.heredoc == NULL;
	if (redirection.status != 0)
		return (free(*payload), redirection);
	is_input_file = ft_strchr(*payload, '<') != NULL; 
	redirection.input_file = make_input_redir(payload);
	redirection.status = is_input_file && redirection.input_file < 0;
	if (redirection.status != 0)
		return (free(*payload), redirection);
	return (redirection);
}


int	make_q_command(t_com_queue *q, t_astnodes *node, char *path)
{
	t_com_node	*new_node;
	t_com_redir redir;
	char		*command_payload;
	
	command_payload = ft_substr(node->value, 0, ft_strlen(node->value));
	if (!command_payload)
		return (-1);
	if ((redir = make_redirection(&command_payload)).status != 0)
		return (free(command_payload), -1);
	if (!(new_node = add_node(q, command_payload, path)))
		return (-1);
	if (redir.output_file != -1)
		new_node->out_file = redir.output_file;
	if (redir.input_file != -1)
		new_node->in_file = redir.input_file;
	if (redir.heredoc)
		new_node->heredoc = redir.heredoc;
	q->nodes = new_node;
	return (0);
}
