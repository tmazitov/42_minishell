/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:48:27 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/21 14:24:22 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

t_com_output	*make_file_output(char *filepath)
{
	t_com_output	*output;

	output = malloc(sizeof(t_com_output));
	if (!output)
		return (NULL);
	output->limiter = NULL;
	output->src = OUTFILE;
	output->filepath = filepath;
	output->fd = open(output->filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
