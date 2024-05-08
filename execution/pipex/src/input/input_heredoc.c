/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:29:55 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/08 16:58:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	is_limiter(char *limiter, char *input)
{
	if (!limiter || !input)
		return (0);
	if (ft_strlen(limiter) != ft_strlen(input))
		return (0);
 	return ft_strncmp(input, limiter, ft_strlen(limiter)) == 0;
}

int	heredoc_fill(t_com_input *heredoc)
{
	char	*input;
	char	*limiter;
	int		fd;

	fd = open(heredoc->filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (1);
	limiter = heredoc->limiter;
	input = readline("> ");
	while (input 
		&& !is_limiter(limiter, input) 
		&& status_code(GET, -1) != STOP_HEREDOC)
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	close(fd);
	free(input);
	if (status_code(GET, -1) == STOP_HEREDOC)
		return (1);
	heredoc->fd = open(heredoc->filepath, O_RDONLY);
	if (fd < 0)
		return (1);
	return (0);
}

t_com_input	*make_heredoc_input(char *limiter)
{
	t_com_input	*input;

	input = malloc(sizeof(t_com_input));
	if (!input)
		return (NULL);
	input->fd = -1;
	input->src = HEREDOC;
	input->limiter = limiter;
	input->filepath = heredoc_temp_filepath();
	if (!input->filepath)
		return (free_heredoc_input(input));
	return (input);
}

void	*free_heredoc_input(t_com_input *input)
{
	if (!input)
		return (NULL);
	if (input->fd > 0)
		close(input->fd);
	if (access(input->filepath, R_OK) != -1)
		unlink(input->filepath);
	if (input->filepath)
		free(input->filepath);
	free(input);
}