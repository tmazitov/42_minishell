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
	if ((ft_isalpha(varname[0]) > 0) || varname[0] == '_')
		return (true);
	else
		return (false);
}

char    *ft_getvarname(char *str, int index)
{
	int     len;
	char    *varname;

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