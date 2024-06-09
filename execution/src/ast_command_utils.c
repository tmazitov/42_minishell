/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:57:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 02:27:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static int	non_space_length(char *str)
{
	int		length;
	int		counter;

	length = 0;
	counter = 0;
	while (str[counter])
	{
		if (str[counter] != ' ')
			length++;
		counter++;
	}
	return (length);
}

char	*filter_spaces(char *str)
{
	char	*new_str;
	int		counter;
	int		new_counter;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (non_space_length(str) + 1));
	if (!new_str)
		return (NULL);
	counter = 0;
	new_counter = 0;
	while (str[counter])
	{
		if (str[counter] != ' ')
			new_str[new_counter++] = str[counter];
		counter++;
	}
	new_str[new_counter] = '\0';
	free(str);
	return (new_str);
}
