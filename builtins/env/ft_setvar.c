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
	// char		*equalsign;
	char		*varname;
	char		*varvalue;
	// char		**var_split;
	t_varlist	*var_head;

	var_head = *varlist;
	varname = ft_splitequalsign(str, ft_strchr(str, '='));
	varvalue = ft_splitequalsign((ft_strchr(str,'=')), ft_strchr(str, '\0'));

	if (!varname || !ft_checkvarname(varname))
		return (ft_printf("%s: command not found\n", str), 0);
	else
		ft_setenv(varname, varvalue, 1, varlist);
	*varlist = var_head;
	return (1);
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

char	*ft_splitequalsign(char *start, char *end)
{
	char	*var;
	int		len;
	int		count;

	count = 0;
	if (*start == '=' && start < end)
		start++;
	len = end - start + 1;
	var = malloc(sizeof(char) * (len));
	while (start < end && count < len - 1)
	{
		var[count] = start[count];
		count++;
	}
	var[count] = '\0';
	return (var);
}