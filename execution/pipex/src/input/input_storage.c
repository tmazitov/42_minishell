/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_storage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:48:01 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/08 16:55:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	infile_amount(char *com_string)
{
	int		amount;
	char	*temp_com;
	char	*infile;

	temp_com = com_string;
	amount = 0;
	while (1)
	{
		if (*temp_com == '\0')
			break;
		if (temp_com == com_string && temp_com[0] == '<' && temp_com[1] == ' ')
		{
			amount++;
			temp_com++;
			continue ;
		}
		infile = ft_strnstr(temp_com, " < ", ft_strlen(temp_com));
		if (!infile)
			break ;
		amount++;
		temp_com = infile + 2;
	}
	return (amount);
}

static int	heredoc_amount(char *com_string)
{
	int		amount;
	char	*temp_com;
	char	*heredoc;

	temp_com = com_string;
	amount = 0;
	while (1)
	{
		if (*temp_com == '\0')
			break;
		heredoc = ft_strnstr(temp_com, "<<", ft_strlen(temp_com));
		if (!heredoc)
			break ;
		amount++;
		temp_com = heredoc + 2;
	}
	return (amount);
}

t_com_input_storage	*make_input_storage(char **com_line)
{	
	t_com_input_storage	*storage;
	int					total_amount;

	storage = malloc(sizeof(t_com_input_storage));
	if (!storage)
		return (NULL);
	storage->content = NULL;
	storage->file_amount = infile_amount(*com_line);
	storage->heredoc_amount = heredoc_amount(*com_line);
	storage->total_amount = storage->file_amount + storage->heredoc_amount;
	if (total_amount == 0)
		return (storage);
	storage->content = malloc(sizeof(t_com_input*) * (storage->total_amount + 1));
	if (!storage->content)
		return (free_input_storage(storage));
	if (fill_input_storage(storage, *com_line))
		return (free_input_storage(storage));
	if (remove_com_line_input(com_line))
		return (free_input_storage(storage));
	return (storage);
}

void	close_all_input(t_com_input_storage *st)
{
	int 		counter;
	t_com_input	*input;

	counter = 0;
	input = st->content[counter];
	while (input)
	{
		if (input->fd > 0)
			close(input->fd);
		input->fd = -1;
		counter++;
		input = st->content[counter];
	}
}

void	*free_input_storage(t_com_input_storage *st)
{
	int 		counter;
	t_com_input	*input;

	if (!st)
		return (NULL);
	if (st->content)
	{
		counter = 0;
		input = st->content[counter];
		while (input)
		{
			if (input->src == INFILE)
				free_file_input(input);
			if (input->src == HEREDOC)
				free_heredoc_input(input);
			counter++;
			input = st->content[counter];
		}
		free(st->content);
	}
	free(st);
}