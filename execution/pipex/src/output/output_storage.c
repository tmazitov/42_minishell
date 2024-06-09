/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_storage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:40:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 02:20:53 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

static int	outfile_amount(char *com_string)
{
	int		amount;
	char	*temp_com;
	char	*outfile;

	temp_com = com_string;
	amount = 0;
	while (1)
	{
		if (*temp_com == '\0')
			break ;
		if (temp_com == com_string && temp_com[0] == '>' && temp_com[1] == ' ')
		{
			amount++;
			temp_com++;
			continue ;
		}
		outfile = ft_strnstr(temp_com, " > ", ft_strlen(temp_com));
		if (!outfile)
			break ;
		amount++;
		temp_com = outfile + 2;
	}
	return (amount);
}

static int	append_outfile_amount(char *com_string)
{
	int		amount;
	char	*temp_com;
	char	*heredoc;

	temp_com = com_string;
	amount = 0;
	while (1)
	{
		if (*temp_com == '\0')
			break ;
		heredoc = ft_strnstr(temp_com, ">>", ft_strlen(temp_com));
		if (!heredoc)
			break ;
		amount++;
		temp_com = heredoc + 2;
	}
	return (amount);
}

t_com_output_storage	*make_output_storage(char **com_line)
{
	t_com_output_storage	*storage;
	int						total;

	storage = malloc(sizeof(t_com_output_storage));
	if (!storage)
		return (NULL);
	storage->content = NULL;
	storage->file_amount = outfile_amount(*com_line);
	storage->append_amount = append_outfile_amount(*com_line);
	storage->total_amount = storage->file_amount + storage->append_amount;
	if (storage->total_amount == 0)
		return (storage);
	total = storage->total_amount;
	storage->content = malloc(sizeof(t_com_output *) * (total + 1));
	if (!storage->content)
		return (free_output_storage(storage));
	if (fill_output_storage(storage, *com_line))
		return (free_output_storage(storage));
	if (remove_com_line_output(com_line))
		return (free_output_storage(storage));
	return (storage);
}

void	close_all_output(t_com_output_storage *st)
{
	int				counter;
	t_com_output	*output;

	counter = 0;
	output = st->content[counter];
	while (output)
	{
		if (output->fd > 0)
			close(output->fd);
		output->fd = -1;
		counter++;
		output = st->content[counter];
	}
}

void	*free_output_storage(t_com_output_storage *st)
{
	int				counter;
	t_com_output	*output;

	if (!st)
		return (NULL);
	if (st->content)
	{
		counter = 0;
		while (counter < st->total_amount)
		{
			output = st->content[counter];
			if (!output)
				break ;
			if (output->src == OUTFILE)
				free_file_output(output);
			else if (output->src == APPENDFILE)
				free_file_append(output);
			counter++;
		}
		free(st->content);
	}
	free(st);
	return (0);
}
