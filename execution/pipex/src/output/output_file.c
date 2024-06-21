/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:48:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 20:55:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

t_com_output	*make_file_output(char *filepath)
{
	t_com_output	*output;

	output = malloc(sizeof(t_com_output));
	if (!output)
		return (NULL);
	output->src = OUTFILE;
	output->filepath = filepath;
	output->fd = open(output->filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (errno == EPERM || errno == EACCES)
	{
		write(2, "minishell: ", 12);
		write(2, output->filepath, ft_strlen(output->filepath));
		write(2, ": Permission denied\n", 21);
		return (output);
	}
	if (output->fd <= 0)
		return (free_file_output(output));
	return (output);
}

void	*free_file_output(t_com_output *output)
{
	if (!output)
		return (NULL);
	if (output->fd > 0)
		close(output->fd);
	if (output->filepath)
		free(output->filepath);
	free(output);
	return (0);
}
