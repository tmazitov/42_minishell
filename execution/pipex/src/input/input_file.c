/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:41 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 20:56:43 by tmazitov         ###   ########.fr       */
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
	if (errno == EPERM || errno == EACCES)
	{
		write(2, "minishell: ", 12);
		write(2, input->filepath, ft_strlen(input->filepath));
		write(2, ": Permission denied\n", 21);
		return (1);
	}
	if (input->fd <= 0)
	{
		write(2, "minishell: ", 12);
		write(2, input->filepath, ft_strlen(input->filepath));
		write(2, ": No such file or directory\n", 29);
		return (1);
	}
	return (0);
}
