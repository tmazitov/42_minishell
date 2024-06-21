/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:29:55 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 22:30:33 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	is_limiter(char *limiter, char *input)
{
	if (!limiter || !input)
		return (0);
	if (ft_strlen(limiter) != ft_strlen(input))
		return (0);
	return (!ft_strncmp(input, limiter, ft_strlen(limiter)));
}

static int	write_one_string(char *str, t_builtin_info info)
{
	int		ch;
	int		len;
	char	*sub_expr;

	ch = 0;
	while (str[ch] && str[ch] != '$')
		ft_printf("%c", str[ch++]);
	while (str[ch] && str[ch] == '$')
	{
		len = 1;
		while (str[ch + len] && str[ch + len] != '$')
			len++;
		sub_expr = ft_substr(str, ch, len);
		if (!sub_expr)
			return (1);
		ft_printexpansion(sub_expr, 1, *info.env, *info.var);
		free(sub_expr);
		ch += len;
	}
	return (0);
}

static int	heredoc_input(t_com_input *heredoc, char *input, int fd, \
	t_builtin_info info)
{
	char	**tokens;
	int		temp_out;
	int		counter;

	(void)heredoc;
	temp_out = 0;
	(void)temp_out;
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (free(input), 1);
	dup2(fd, STDOUT_FILENO);
	counter = 0;
	while (tokens[counter])
	{
		if (write_one_string(tokens[counter], info))
		{
			dup2(temp_out, STDOUT_FILENO);
			return (free_pointer(tokens), free(input), 1);
		}
		ft_printf(" ");
		counter++;
	}
	ft_printf("\n");
	dup2(temp_out, STDOUT_FILENO);
	return (free_pointer(tokens), free(input), 0);
}

int	heredoc_fill(t_com_input *heredoc, t_builtin_info info)
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
		heredoc_input(heredoc, input, fd, info);
		input = readline("> ");
		if (!input)
			return (close(fd), 2);
	}
	close(fd);
	free(input);
	if (status_code(GET, -1) == STOP_HEREDOC)
		return (1);
	heredoc->fd = open(heredoc->filepath, O_RDONLY);
	return (fd < 0);
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
