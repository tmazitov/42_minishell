/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:41 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 00:20:00 by tmazitov         ###   ########.fr       */
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
