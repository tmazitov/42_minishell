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

int	ft_setvarname(char *str, t_varlist **varlist)
{
	char		*equalsign;
	char		**var_split;
	t_varlist	*var_head;

	var_head = *varlist;
	equalsign = ft_strchr(str, '=');
	if (equalsign)
	{
		var_split = ft_split(str, '=');
		if (ft_strlen_dp(var_split) == 1)
			var_split = ft_realloc_dp(var_split, "", 2);
	}
	else
		return (0);
	if (!ft_checkvarname(var_split[0]))
	{
		ft_printf("%s: command not found\n", str);
		return (0);
	}
	else
		ft_setenv(var_split[0], var_split[1], 1, varlist);
	*varlist = var_head;
	return (free(var_split), 1);
}

int	ft_setenv(char *varname, char *varvalue, int overwrite, t_varlist **varlist)
{
	if ((*varlist)->varname == NULL && (*varlist)->value == NULL)
	{
		(*varlist)->varname = varname;
		(*varlist)->value = varvalue;
		(*varlist)->next = NULL;
		return (1);
	}
	while ((*varlist) != NULL && overwrite > 0 )
	{
		if (ft_strncmp(varname, (*varlist)->varname, ft_strlen(varname)) == 0)
		{
			(*varlist)->value = varvalue;
			break ;
		}
		else if ((*varlist)->next == NULL)
		{
			(*varlist)->next = ft_create_var(varname, varvalue);
			break ;
		}
		else
			(*varlist) = (*varlist)->next;
	}
	return (1);
}
