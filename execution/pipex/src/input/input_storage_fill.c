/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_storage_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:12:01 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/21 14:21:12 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static t_input_src	take_next_input_src(char **com_string)
{
	char	*temp;
	int		counter;

	counter = 0;
	temp = *com_string;
	while (temp[counter])
	{
		if (temp[counter] == '<')
		{
			*com_string = temp + counter + 2;
			if (temp[counter + 1] == '<')
			{
				*com_string = *com_string + 1;
				return (HEREDOC);
			}
			else
				return (INFILE);
		}
		counter++;
	}
	return (0);
}

static int	ft_strlen_zero(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] && str[counter] != ' ')
		counter++;
	return (counter);
}

int	fill_input_storage(t_com_input_storage *st,char *com_string)
{
	char		*temp;
	t_input_src	src_type;
	char		*src_arg;
	int			counter;

	counter = 0;
	temp = com_string;
	while (counter < st->total_amount)
	{
		src_type = take_next_input_src(&temp);
		if (src_type == 0)
			break ;
		src_arg = ft_substr(temp, 0, ft_strlen_zero(temp));
		if (!src_arg)
			return (1);
		if (src_type == HEREDOC)
			st->content[counter] = make_heredoc_input(src_arg);
		else if (src_type == INFILE)
			st->content[counter] = make_file_input(src_arg);
		if (!st->content[counter])
			return (1);
		counter++;
	}
	st->content[counter] = NULL;
	return (0);
}

int	fill_command_heredoc(t_com_input_storage *storage)
{
	int			counter;
	t_com_input	*input;

	counter = 0;
	input = storage->content[counter];
	while (input)
	{
		if (input->src == HEREDOC)
		{
			status_code(SET, IN_HEREDOC);
			if (heredoc_fill(input))
				return (1);
		}
		counter++;
		input = storage->content[counter];
	}
	return (0);
}

int	open_command_infile(t_com_input_storage	*storage)
{
	int			counter;
	t_com_input	*input;

	counter = 0;
	input = storage->content[counter];
	while (input)
	{
		if (input->src == INFILE)
		{
			if (file_input_open(input))
				return (1);
		}
		counter++;
		input = storage->content[counter];
	}
	return (0);
}
