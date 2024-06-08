/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_filter_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 09:12:21 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 02:17:23 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

static char	*merge(char *str1, char *str2, char **result)
{
	*result = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (*result);
}

static int	skip(char *line, int *start)
{
	int	counter;

	counter = *start;
	while (line[counter] && line[counter] == '>')
		counter++;
	*start = counter;
	if (!line[counter])
		return (counter);
	*start += 1;
	return (counter + 1);
}

static int	skip_arg(char *line, int *start)
{
	int	counter;

	counter = *start;
	while (line[counter] && line[counter] != ' ')
		counter++;
	*start = counter;
	if (!line[counter])
		return (counter);
	*start += 1;
	return (counter + 1);
}

int	remove_com_line_output(char **com)
{
	int		s;
	int		end;
	char	*line;
	char	*temp;
	char	*r;

	line = *com;
	temp = NULL;
	r = ft_calloc((s = 0) + 1, sizeof(char));
	if (!r)
		return (1);
	while (line[s])
	{
		end = s;
		while (line[end] && line[end] != '>')
			end++;
		if (end - s != 0 && !(merge(r, ft_substr(*com, s, end - s), &temp)))
			return (free(r), 1);
		if (temp)
			r = temp;
		s = end;
		if (!line[s] || !line[skip(line, &s)] || !line[skip_arg(line, &s)])
			break ;
	}
	return (free(*com), (*com = r), 0);
}

// int main(int ac, char *av[])
// {
// 	if (ac != 2)
// 		return (1);
// 	char * cp1 = ft_substr(av[1], 0, ft_strlen(av[1]));
// 	char * cp2 = ft_substr(av[1], 0, ft_strlen(av[1]));
// 	int	status = remove_com_line_output(&cp2);

// 	if (status != 0)
// 		return (free(cp1), free(cp2), status);

// 	printf("SRC : '%s'\tRES : '%s'\n", cp1, cp2);
// 	free(cp1);
// 	free(cp2);
// 	return (0);
// }
