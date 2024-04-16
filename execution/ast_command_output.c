/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:42:39 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/16 19:43:57 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	fd_by_last_output(char **out_paths)
{
	int 	output_fd;
	int		counter;
	char	*path;

	if (!out_paths)
		return (-1);
	output_fd = -1;
	counter = 0;
	while (out_paths[counter])
	{
		if (output_fd != -1)
			close(output_fd);
		if (ft_strchr(out_paths[counter], ' '))
			out_paths[counter] = filter_spaces(out_paths[counter]);
		path = out_paths[counter];
		output_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (output_fd <= 0)
			return (-1);
		counter++;
	}
	return (output_fd);
}
/// @brief Open each one outfile and return a file descriptor of the last one.
/// @param com_payload pointer to the user input
/// @return File descriptor of the last output file
int	make_com_output(char **com_payload)
{
	char		**com_parts;
	char		*new_payload;
	int			output_fd;
	
	if (!*com_payload || !ft_strchr(*com_payload, '>'))
		return (-1);
	com_parts = ftt_split(*com_payload, '>');
	if (!com_parts)
		return (-1);
	output_fd = fd_by_last_output(com_parts + 1);
	if (output_fd <= 0)
		return (free_split(com_parts), -1);
	new_payload = ft_substr(com_parts[0], 0, ft_strlen(com_parts[0]));
	if (!new_payload)
		return (free_split(com_parts), -1);
	free(*com_payload);
	*com_payload = new_payload;
	free_split(com_parts);
	return (output_fd);
}
