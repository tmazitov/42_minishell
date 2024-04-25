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
	if ((ft_isalpha(varname[0]) > 0) || ft_strncmp(varname, "_", 1) == 0)
		return (true);
	else
		return (false);
}

char	*ft_getvarname(char *str, int index)
{
	int		len;
	char	*varname;

	len = 0;
	while (str[index + len] != '\0' && !ft_isspace(str[index + len]) \
		&& str[index + len] != '\"')
		len++;
	varname = malloc(sizeof(char) * (len + 2));
	if (!varname)
		return (NULL);
	ft_strlcpy(varname, &str[index], len + 1);
	varname[index + len + 2] = '\0';
	if (ft_checkvarname(varname))
		return (varname);
	else
		return (NULL);
}

/// @brief print arguments inside double quotes
/// @param str string with double quotes
void	ft_printdquotes(char *str, t_envlist *envlist, t_varlist *varlist)
{
	int	len;

	len = 0;
	str++;
	while (str[len] != '\"' && str[len] != '\0')
	{
		if (str[len] == '$')
		{
			ft_printexpansion(str, ++len, envlist, varlist);
			while (!ft_isspace(str[len]) && str[len] != '\0' && \
					str[len] != '\"')
				len++;
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
