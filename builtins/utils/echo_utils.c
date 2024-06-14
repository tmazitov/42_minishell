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
	if ((ft_isdigit(varname[0]) > 0 && ft_strlen(varname) == 1))
		return (true);
	if ((ft_isdigit(varname[0]) > 0 && ft_strlen(varname) > 0) || \
		(((ft_isalpha(varname[0]) == 0)) && ft_strncmp("_", varname, 1) != 0))
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

int	ft_countvarname(char *varname)
{
	int	count;

	count = 0;
	if ((ft_isdigit(varname[0]) > 0) || ((((ft_isalpha(*varname) == 0) && \
		(*varname != '_')) && (ft_isdigit(*varname) == 0))))
		return (1);
	varname++;
	count++;
	while (*varname)
	{
		if (((ft_isalpha(*varname) == 0) && (*varname != '_')) && \
			(ft_isdigit(*varname) == 0))
			return (count);
		varname++;
		count++;
	}
	return (count);
}

char	*ft_getvarname(char *str, int index)
{
	int		len;
	char	*varname;
	int		count;

	len = ft_countvarname(&str[index]);
	varname = malloc(sizeof(char) * (len + 1));
	if (!varname)
		return (NULL);
	ft_bzero(varname, len + 1);
	count = 0;
	while (count < len)
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

	(void)envlist;
	(void)varlist;
	len = 0;
	str++;
	while (str[len] != '\0')
	{
		if (str[len] != '\"')
			write(1, &str[len++], 1);
		else
			len++;
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
