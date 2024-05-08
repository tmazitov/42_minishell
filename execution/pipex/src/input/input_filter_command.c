/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_filter_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:37:34 by tmazitov          #+#    #+#             */
/*   Updated: 2024/05/07 18:50:22 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include <stdio.h>

static char	*ft_strjoin_clean(char *str1, char *str2)
{
	char	*result;

	result = ft_strjoin(str1, str2);
	if (ft_strlen(str1) > 0)
		free(str1);
	if (ft_strlen(str2) > 0)
		free(str2);
	return (result);
}

static int	skip_redir(char *line, int start)
{
	int counter;

	counter = start;
	while (line[counter] && line[counter] == '<')
		counter++;
	if (!line[counter])
		return (counter);
	return (counter + 1);
}

static int	skip_redir_arg(char *line, int start)
{
	int counter;

	counter = start;
	while (line[counter] && line[counter] != ' ')
		counter++;
	if (!line[counter])
		return (counter);
	return (counter + 1);
}

int	remove_com_line_input(char **com)
{
	int		start;
	int		end;
	char	*line;
	char	*temp;
	char	*result;

	line = *com;
	start = 0;
	temp = NULL;
	result = "";
	while (line[start])
	{
		end = start;
		while (line[end] && line[end] != '<')
			end++;
		if (end-start != 0 
			&& !(temp = ft_strjoin_clean(result, ft_substr(*com, start, end-start))))
			return (free(result), 1);
		if (temp)
			result = temp;
		if (!line[(start = end)]
			|| !line[(start = skip_redir(line, start))]
			|| !line[(start = skip_redir_arg(line, start))])
			break ;
	}
	if (ft_strlen(result) == 0)
		return (0);
	free(*com);
	*com = result;
	return (0);
}

// int main(int ac, char *av[])
// {
// 	if (ac != 2)
// 		return (1);
// 	char * cp1 = ft_substr(av[1], 0, ft_strlen(av[1]));
// 	char * cp2 = ft_substr(av[1], 0, ft_strlen(av[1]));
// 	int	status = remove_com_line_input(&cp2);

// 	if (status != 0)
// 		return (free(cp1), free(cp2), status);

// 	printf("SRC : '%s'\tRES : '%s'\n", cp1, cp2);
// 	free(cp1);
// 	free(cp2);
// 	return (0);
// }
