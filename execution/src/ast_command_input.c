/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:04:42 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/20 03:23:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	fd_by_last_input(char **new_payload)
{
	int 	input_fd;
	int		len;
	char	*path;
	char	*path_start;

	if (!new_payload || !*new_payload)
		return (-1);
	input_fd = -1;
	while (ftt_strnstr(*new_payload, "< ", ft_strlen(*new_payload)))
	{
		if (input_fd != -1)
			close(input_fd);
		path_start = *new_payload;
		path_start += 1;
		while (*path_start == ' ')
			path_start += 1;
		len = 0;
		while (path_start[len] && path_start[len] != ' ' && path_start[len] != '<')
			len++;
		path = ft_substr(path_start, 0, len);
		if (!path)
			return (-1);
		input_fd = open(path, O_RDONLY, 0777);
		free(path);
		if (input_fd <= 0)
			return (-1);
		path_start += len;
		while (*path_start == ' ')
			path_start += 1;
		*new_payload = path_start;
		printf("new_payload : '%s'\n", *new_payload);
	}
	return (input_fd);
}
/// @brief Open each one infile and return a file descriptor of the last one.
/// @param com_payload pointer to the user input
/// @return File descriptor of the last input file
int	make_com_input(char **com_payload)
{
	char		*new_payload;
	int			input_fd;
	
	if (!*com_payload || !ft_strchr(*com_payload, '<'))
		return (-1);
	new_payload = *com_payload;
	input_fd = fd_by_last_input(&new_payload);
	if (input_fd <= 0)
		return (-1);
	new_payload = ft_substr(new_payload, 0, ft_strlen(new_payload));
	if (!new_payload)
		return (-1);
	free(*com_payload);
	*com_payload = new_payload;
	return (input_fd);
}
