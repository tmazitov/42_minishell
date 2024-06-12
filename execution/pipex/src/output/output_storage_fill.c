/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_storage_fill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:00:26 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/10 18:19:39 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

static t_output_dest	take_next_output_dest(char **com_string)
{
	char	*temp;
	int		counter;

	counter = 0;
	temp = *com_string;
	while (temp[counter])
	{
		if (temp[counter] == '>')
		{
			*com_string = temp + counter + 2;
			if (temp[counter + 1] == '>')
			{
				*com_string = *com_string + 1;
				return (APPENDFILE);
			}
			else
				return (OUTFILE);
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

int	fill_output_storage(t_com_output_storage *st, char *com_string)
{
	char			*temp;
	t_output_dest	dest_type;
	char			*dest_arg;
	int				counter;

	counter = 0;
	temp = com_string;
	while (counter < st->total_amount)
	{
		dest_type = take_next_output_dest(&temp);
		if (!dest_type)
			break ;
		dest_arg = ft_substr(temp, 0, ft_strlen_zero(temp));
		if (!dest_arg)
			return (1);
		if (dest_type == OUTFILE)
			st->content[counter] = make_file_output(dest_arg);
		else if (dest_type == APPENDFILE)
			st->content[counter] = make_file_append(dest_arg);
		if (!st->content[counter])
			return (1);
		counter++;
	}
	st->content[counter] = NULL;
	return (0);
}
