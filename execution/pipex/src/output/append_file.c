/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:59:23 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/24 16:01:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

t_com_output	*make_file_append(char *filepath)
{
	t_com_output	*output;

	output = malloc(sizeof(t_com_output));
	if (!output)
		return (NULL);
	output->src = APPENDFILE;
	output->filepath = filepath;
	output->fd = open(output->filepath, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (output->fd <= 0)
		return (free_file_output(output));
	return (output);
}

void	*free_file_append(t_com_output *output)
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
