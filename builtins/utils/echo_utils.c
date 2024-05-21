/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkgrammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:08 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 18:35:51 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

bool	ft_checkvarname(char *varname)
{
	if ((ft_isdigit(varname[0]) > 0) || (((ft_isalpha(varname[0]) == 0)) && \
		ft_strncmp("_", varname, 1) != 0))
		return (false);
	varname++;
	while (*varname)
	{
		if (((ft_isalpha(*varname) == 0) && (*varname != '_')) && \
			(ft_isdigit(*varname) == 0))
			return (false);
		varname++;
	}
	return (true);
}

char	*ft_getvarname(char *str, int index)
{
	int		len;
	char	*varname;
	int		count;

	len = 0;
	while (str[index + len] != '\0' && !ft_isspace(str[index + len]) \
		&& str[index + len] != '\"')
		len++;
	varname = malloc(sizeof(char) * (len + 1));
	if (!varname)
		return (NULL);
	ft_bzero(varname, len + 1);
	count = 0;
	while (str[index + count] != '\0' && !ft_isspace(str[index + count]) \
		&& str[index + count] != '\"')
	{
		varname[count] = str[index + count];
		count++;
	}
	if (ft_checkvarname(varname))
		return (varname);
	else
		return (free(varname), NULL);
}

/// @brief print arguments inside double quotes
/// @param str string with double quotes
void	ft_printdquotes(char *str, t_envlist *envlist, t_varlist *varlist)
{
	int	len;

	len = 0;
	str++;
	while (str[len] != '\0' && str[len] != '\"')
	{
		if (str[len] == '$')
		{
			if (str[len + 1] == ' ' || str[len + 1] == '\"')
				ft_printf("%c", str[len++]);
			else if (str[len + 1] == '?')
			{
				ft_printf("0");
				len += 2;
			}
			else
			{
				ft_printexpansion(str, ++len, envlist, varlist);
				while (!ft_isspace(str[len]) && str[len] != '\0' && \
						str[len] != '\"')
					len++;
			}
		}
		else
			write(1, &str[len++], 1);
	}
}

/// @brief print arguemnts inside single quotes, retaining its literal meaning
/// @param str string with single quotes
void	ft_printsquotes(char *str)
{
	int	len;

	len = 0;
	str++;
	while (str[len] != '\'' && str[len] != '\0')
	{
		write(1, &str[len], 1);
		len++;
	}
}
