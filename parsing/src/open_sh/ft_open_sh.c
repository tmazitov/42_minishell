/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_sh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:23:02 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 02:20:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

bool	ft_check_args(char **str_split)
{
	if (!(ft_checkiffile(str_split[1])))
		return (false);
	else
		return (true);
}

bool	ft_checkiffile(char	*str)
{
	char	*extnsn;

	if (str == NULL)
		return (false);
	extnsn = ft_strchr_gnl(str + 1, '.');
	if (!extnsn)
		return (false);
	else
		return (true);
}

bool	check_fd(char *str)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("bash: %s: No such file or directory\n", str);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

bool	ft_checkshfile(char *str)
{
	char	*cmd;
	char	**str_split;

	cmd = "minishell";
	str_split = ft_split(str, ' ');
	if (ft_strncmp(cmd, str_split[0], ft_strlen(cmd)) != 0)
		return (free_pointer(str_split), false);
	if (!ft_check_args(str_split))
	{
		parse_input(str);
		return (free_pointer(str_split), false);
	}
	else if (!check_fd(str_split[1]))
		return (free_pointer(str_split), false);
	else
		return (free_pointer(str_split), true);
}

void	ft_openshfile(char *str_input)
{
	char	*str_line;
	char	**str_split;
	int		fpointer;

	str_split = ft_split(str_input, ' ');
	str_line = malloc(sizeof(char) * 1);
	fpointer = open(str_split[1], 256);
	while (str_line != NULL)
	{
		free(str_line);
		str_line = get_next_line(fpointer);
		parse_input(str_line);
	}
	free_pointer(str_split);
}

// int	get_fd(char *argv)
// {
// 	char	*filedirectory;
// 	int		fd;

// 	filedirectory = argv;
// 	fd = open(filedirectory, O_RDONLY);
// 	return (fd);
// }