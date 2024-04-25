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

int	ft_unsetvarname(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	**var_split;
	int		result;
	int		count;
	t_varlist	*head;

	result = 0;
	var_split = ft_split(str, ' ');
	if (ft_strlen_dp(var_split) == 1)
	{
		ft_printf("unset: not enough arguments\n");
		return (0);
	}
	count = 1;
	while (var_split[count] != NULL)
	{
		head = *varlist;
		if (!ft_checkvarname(var_split[count]))
		{
			ft_printf("unset: %s: invalid parameter name\n", var_split[count]);
			return (free_pointer(var_split), 0);
		}
		result = ft_unsetenv(var_split[count], envlist, varlist);
		if (result != 2)
			*varlist = head;
		count++;
	}
	if (*varlist == NULL)
		*varlist = ft_init_var();
	return (free_pointer(var_split), 1);
}

int	ft_unsetenv(char *varname, t_envlist **envlist, t_varlist **varlist)
{
	t_envlist	*head;
	t_envlist	*prev_env;
	t_envlist	*curr_env;

	prev_env = NULL;
	head = (*envlist);
	// ft_printf("ft_unsetvar\n");
	if ((*envlist) != NULL && (*envlist)->varname != NULL && ft_strncmp(varname, (*envlist)->varname, ft_strlen(varname)) == 0)
	{
		curr_env = *envlist;
		free(curr_env);
		*envlist = (*envlist)->next;
		return (2);
	}
	while ((*envlist) != NULL && ft_strncmp(varname, (*envlist)->varname, ft_strlen(varname)) != 0)
	{
		// ft_printf("envlist varname: %s\n", (*envlist)->varname);
		prev_env = (*envlist);
		(*envlist) = (*envlist)->next;
	}
	if (prev_env == NULL && (*envlist) != NULL)
	{
		// ft_printf("prev_env == NULL\n");
		*envlist = (*envlist)->next;
	}
	else if ((*envlist) != NULL)
	{
		// ft_printf("(*envlist) != NULL\n");
		prev_env->next = (*envlist)->next;
		free((*envlist));
	}
	else
	{
		*envlist = head;
		return (ft_unsetvar(varname, varlist));
	}
	*envlist = head;
	return (ft_unsetvar(varname, varlist), 1);
}

int	ft_unsetvar(char *varname, t_varlist **varlist)
{
	t_varlist	*curr_var;
	t_varlist	*head;
	t_varlist	*prev_var;

	prev_var = NULL;
	head = (*varlist);
	// ft_printf("ft_unsetvar\n");
	if ((*varlist) != NULL && (*varlist)->varname != NULL && ft_strncmp(varname, (*varlist)->varname, ft_strlen(varname)) == 0)
	{
		curr_var = *varlist;
		free(curr_var);
		*varlist = (*varlist)->next;
		return (2);
	}
	// ft_printf("ft_unsetvar\n");
	while ((*varlist) != NULL && (*varlist)->varname != NULL && ft_strncmp(varname, (*varlist)->varname, ft_strlen(varname)) != 0)
	{
		// ft_printf("varlist varname: %s\n", (*varlist)->varname);
		prev_var = (*varlist);
		(*varlist) = (*varlist)->next;
	}
	if (prev_var == NULL && (*varlist) != NULL)
	{
		// ft_printf("prev_var == NULL\n");
		*varlist = (*varlist)->next;
	}
	else if ((*varlist) != NULL && (*varlist)->varname != NULL)
	{
		// ft_printf("curr_var != NULL\n");
		prev_var->next = (*varlist)->next;
		free((*varlist));
	}
	else
	{
		*varlist = head;
		return (0);
	}
	*varlist = head;
	return (1);
}