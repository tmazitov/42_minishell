/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_storage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:00:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	*free_input_storage(t_com_input_storage *st)
{
	int			counter;
	t_com_input	*input;

	if (!st)
		return (NULL);
	if (st->content)
	{
		counter = 0;
		input = st->content[counter];
		while (input)
		{
			if (input->src == INFILE)
				free_file_input(input);
			else if (input->src == HEREDOC)
				free_heredoc_input(input);
			counter++;
			input = st->content[counter];
		}
		free(st->content);
	}
	free(st);
	return (0);
}

void	*free_heredoc_input(t_com_input *input)
{
	if (!input)
		return (NULL);
	if (input->fd > 0)
		close(input->fd);
	if (access(input->filepath, R_OK) != -1)
		unlink(input->filepath);
	if (input->limiter)
		free(input->limiter);
	if (input->filepath)
		free(input->filepath);
	free(input);
	return (0);
}

void	*free_file_input(t_com_input *input)
{
	if (!input)
		return (NULL);
	if (input->fd > 0)
		close(input->fd);
	if (input->filepath)
		free(input->filepath);
	if (input->limiter)
		free(input->limiter);
	free(input);
	return (0);
}
