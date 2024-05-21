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
	char		**var_split;
	int			count;
	t_varlist	*head;

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
		if (ft_unsetenv(var_split[count++], envlist, varlist) != 2)
			*varlist = head;
	}
	if (*varlist == NULL)
		*varlist = ft_init_var();
	return (free_pointer(var_split), 1);
}

int	ft_unsetenv(char *varname, t_envlist **envlist, t_varlist **varlist)
{
	t_envlist	*head;
	t_envlist	*prev_env;

	prev_env = NULL;
	head = (*envlist);
	if ((*envlist) != NULL && (*envlist)->varname != NULL && \
		ft_strncmp(varname, (*envlist)->varname, ft_strlen(varname)) == 0)
	{
		free(*envlist);
		*envlist = (*envlist)->next;
		return (2);
	}
	while ((*envlist) != NULL && (*envlist)->varname != NULL && \
		ft_strncmp(varname, (*envlist)->varname, ft_strlen(varname)) != 0)
	{
		prev_env = (*envlist);
		(*envlist) = (*envlist)->next;
	}
	if ((*envlist) != NULL && (*envlist)->varname != NULL)
	{
		prev_env->next = (*envlist)->next;
		free((*envlist));
	}
	*envlist = head;
	return (ft_unsetvar(varname, varlist));
}

int	ft_unsetvar(char *varname, t_varlist **varlist)
{
	t_varlist	*head;
	t_varlist	*prev_var;
	t_varlist	*curr_var;

	prev_var = NULL;
	head = (*varlist);
	if ((*varlist) != NULL && (*varlist)->varname != NULL && \
		ft_strncmp(varname, (*varlist)->varname, ft_strlen(varname)) == 0)
	{
		curr_var = (*varlist);
		// free(*varlist);
		*varlist = (*varlist)->next;
		free(curr_var);
		return (2);
	}
	while ((*varlist) != NULL && (*varlist)->varname != NULL && \
		ft_strncmp(varname, (*varlist)->varname, ft_strlen(varname)) != 0)
	{
		prev_var = (*varlist);
		(*varlist) = (*varlist)->next;
	}
	if ((*varlist) != NULL && (*varlist)->varname != NULL)
	{
		prev_var->next = (*varlist)->next;
		free((*varlist));
	}
	*varlist = head;
	return (1);
}
// if (prev_var == NULL && (*varlist) != NULL)
// 	*varlist = (*varlist)->next;