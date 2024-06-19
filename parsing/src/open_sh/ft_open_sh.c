/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_sh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:23:02 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 21:27:21 by emaravil         ###   ########.fr       */
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

/// @brief check if the argument is a file
/// @param str filepath and filename
/// @return true if file, false otherwise
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

/// @brief check filedirectory if valid or exists
/// @param str filepath
/// @return true if file exists, false if not
bool	check_fd(char *str)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_err_p("bash: ", str, ": No such file or directory\n");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

/// @brief check if the first command is "minishell". This means that the 
/// user wants to open an sh file.
/// @brief checs the second argument if it is a valid sh file, or if the file
/// exists
/// @param str string command from readline
/// @return true if trying to open sh file, false if not
bool	ft_checkshfile(char *str)
{
	char	**str_split;
	char	*str_temp;
	int		count;

	count = 0;
	if (!*str || !str)
		return (false);
	str_split = ft_split(str, ' ');
	if (!str_split)
		return (false);
	while (str_split[count])
	{
		str = ft_strstr(str_split[count], ".sh");
		str_temp = ft_cleanopensh(str);
		if (str_temp && ft_strstr(str_temp, ".sh") && \
			(ft_strlen(str_temp) == 3))
		{
			free(str_temp);
			return (free_pointer(str_split), true);
		}
		free(str_temp);
		count++;
	}
	return (free_pointer(str_split), false);
}

/// @brief open sh file and read the contents. then parse each line of command
/// @param str_input command input with "minishell" and "filepath/filename"
void	ft_openshfile(char *str_input)
{
	char	*str_line;
	char	**str_split;
	int		fpointer;

	str_split = ft_split(str_input, ' ');
	str_line = malloc(sizeof(char) * 1);
	if (str_line == NULL)
		return ;
	fpointer = open(str_split[1], 256);
	while (str_line != NULL)
	{
		free(str_line);
		str_line = get_next_line(fpointer);
	}
	free_pointer(str_split);
	free(str_line);
}
