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

int	ft_setvar(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char		**var;
	int			index;
	t_varlist	*var_head;
	int			exit_status;

	index = -1;
	exit_status = 0;
	var_head = *varlist;
	var = ft_splittoken_setvar(str);
	var = str_token(var);
	var = ft_handlesetvarsplit(str, var);
	if (!var)
		return (127);
	while (var[++index] != NULL)
	{
		if (ft_setvarname(var[index], envlist, varlist) == 0)
		{
			ft_err_b(var[index], ": command not found\n", NULL);
			exit_status = 127;
			break ;
		}
	}
	*varlist = var_head;
	return (free_pointer(var), exit_status);
}

int	ft_setvarlist(char *varname, char *varvalue, int overwrite, \
	t_varlist **varlist)
{
	if ((*varlist)->varname == NULL && (*varlist)->value == NULL)
	{
		(*varlist)->varname = varname;
		(*varlist)->value = varvalue;
		(*varlist)->next = NULL;
		return (1);
	}
	while ((*varlist) != NULL && overwrite > 0)
	{
		if (ft_compname(varname, (*varlist)->varname))
		{
			ft_doublefree((*varlist)->value, varname);
			(*varlist)->value = varvalue;
			return (2);
		}
		else if ((*varlist)->next == NULL)
		{
			(*varlist)->next = ft_create_var(varname, varvalue);
			return (1);
		}
		else
			(*varlist) = (*varlist)->next;
	}
	return (ft_doublefree(varname, varvalue), 3);
}

int	ft_setvarname(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	*varname;
	char	*varvalue;

	if (ft_strchr(str, '='))
		varname = ft_splitequalsign(str, ft_strchr(str, '='), envlist, varlist);
	else
		varname = ft_strdup(str);
	if (ft_strchr(str, '='))
		varvalue = ft_splitequalsign(ft_strchr(str, '='), \
			ft_strchr(str, '\0'), envlist, varlist);
	else
		varvalue = NULL;
	if (!varname || !ft_checkvarname(varname))
		return (ft_doublefree(varname, varvalue), 0);
	else
	{
		ft_setvarlist(ft_strdup(varname), ft_strdup(varvalue), 1, varlist);
		if (ft_checkvarenv(varname, *envlist))
			ft_setenvlist(ft_strdup(varname), ft_strdup(varvalue), 1, envlist);
		ft_doublefree(varname, varvalue);
	}
	return (1);
}

void	ft_doublefree(char	*str1, char	*str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

int	ft_setenvlist(char *varname, char *varvalue, int overwrite, \
	t_envlist **envlist)
{
	if ((*envlist)->varname == NULL && (*envlist)->value == NULL)
	{
		(*envlist)->varname = varname;
		(*envlist)->value = varvalue;
		(*envlist)->next = NULL;
		return (1);
	}
	while ((*envlist) != NULL && overwrite > 0)
	{
		if (ft_compname(varname, (*envlist)->varname))
		{
			ft_doublefree((*envlist)->value, varname);
			(*envlist)->value = varvalue;
			return (2);
		}
		else if ((*envlist)->next == NULL)
		{
			(*envlist)->next = ft_create_env(NULL, varname, varvalue);
			return (1);
		}
		else
			(*envlist) = (*envlist)->next;
	}
	return (ft_doublefree(varname, varvalue), 3);
}
