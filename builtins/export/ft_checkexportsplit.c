/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkexportsplit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:09:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 17:57:38 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

bool	ft_checkexportsplit(char *str, char *prevvar, char *currvar)
{
	char	*str_temp;

	if (((size_t)(ft_strstr(str + ft_strlen(prevvar), \
		currvar) - ft_strstr(str, prevvar)) == ft_strlen(prevvar)))
		return (true);
	else if (ft_strstr(prevvar, currvar))
	{
		str_temp = ft_strstr(prevvar, currvar);
		prevvar = ft_strstr(str, str_temp);
		while (*prevvar == *str_temp)
		{
			if (*(prevvar + 1) != *(str_temp + 1))
				break ;
			prevvar++;
			str_temp++;
		}
		currvar = ft_strstr(prevvar, currvar);
		if ((prevvar) && (((ft_strlen(prevvar) - ft_strlen(currvar)) == 1)))
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	ft_checkvarenv(char *varname, t_envlist *envlist)
{
	while (envlist != NULL && envlist->varname != NULL)
	{
		if (ft_compname(varname, envlist->varname))
		{
			return (true);
		}
		else
			envlist = envlist->next;
	}
	return (false);
}
