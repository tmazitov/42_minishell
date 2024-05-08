/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:41 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/08 12:41:12 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_com_input	*make_file_input(char *filepath)
{
	t_com_input	*input;

	input = malloc(sizeof(t_com_input));
	if (!input)
		return (NULL);
	input->limiter = NULL;
	input->src = INFILE;
	input->filepath = filepath;
	input->fd = -1;
	return (input);
}

int	file_input_open(t_com_input *input)
{
	input->fd = open(input->filepath, O_RDONLY);
	if (input->fd <= 0)
		return (1);
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
	free(input);
}