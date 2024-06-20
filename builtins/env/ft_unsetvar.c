/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:32:40 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/13 19:32:40 by emaravil         ###   ########.fr       */
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
		return (free_pointer(var_split), 0);
	count = 1;
	while (var_split[count] != NULL)
	{
		head = *varlist;
		if (!ft_checkvarname(var_split[count]))
		{
			ft_err_b("unset: ", var_split[count], \
				": invalid parameter name\n");
			return (free_pointer(var_split), 1);
		}
		if (ft_unsetenv(var_split[count++], envlist, varlist) != 2)
			*varlist = head;
	}
	if (*varlist == NULL)
		*varlist = ft_init_var();
	return (free_pointer(var_split), 0);
}

int	ft_unsetenv_b(char *varname, t_envlist **envlist, t_varlist **varlist)
{
	t_envlist	*prev_env;
	t_envlist	*curr_env;

	(void)varlist;
	while ((*envlist) != NULL && (*envlist)->varname != NULL && \
		ft_strncmp(varname, (*envlist)->varname, ft_strlen((*envlist)->\
		varname)) != 0)
	{
		prev_env = (*envlist);
		(*envlist) = (*envlist)->next;
	}
	if ((*envlist) != NULL && (*envlist)->varname != NULL)
	{
		curr_env = *envlist;
		prev_env->next = (*envlist)->next;
		free((*envlist)->varname);
		free((*envlist)->value);
		free(curr_env);
	}
	return (1);
}

int	ft_unsetenv(char *varname, t_envlist **envlist, t_varlist **varlist)
{
	t_envlist	*head;
	t_envlist	*curr_env;

	head = (*envlist);
	if ((*envlist) != NULL && (*envlist)->varname != NULL && \
		ft_strncmp(varname, (*envlist)->varname, ft_strlen((*envlist)->\
		varname)) == 0 && (ft_strlen(varname) == ft_strlen((*envlist)->\
		varname)))
	{
		curr_env = *envlist;
		*envlist = (*envlist)->next;
		free(curr_env->varname);
		free(curr_env->value);
		free(curr_env);
		return (2);
	}
	ft_unsetenv_b(varname, envlist, varlist);
	*envlist = head;
	return (ft_unsetvar(varname, varlist));
}

int	ft_unsetvar_b(char *varname, t_varlist **varlist)
{
	t_varlist	*prev_var;

	while ((*varlist) != NULL && (*varlist)->varname != NULL && \
		ft_strncmp(varname, (*varlist)->varname, ft_strlen((*varlist)->\
		varname)) != 0)
	{
		prev_var = (*varlist);
		(*varlist) = (*varlist)->next;
	}
	if ((*varlist) != NULL && (*varlist)->varname != NULL)
	{
		prev_var->next = (*varlist)->next;
		free((*varlist)->varname);
		free((*varlist)->value);
		free((*varlist));
	}
	return (1);
}

int	ft_unsetvar(char *varname, t_varlist **varlist)
{
	t_varlist	*head;
	t_varlist	*curr_var;

	head = (*varlist);
	if ((*varlist) != NULL && (*varlist)->varname != NULL && \
		ft_strncmp(varname, (*varlist)->varname, ft_strlen((*varlist)->\
		varname)) == 0 && (ft_strlen(varname) == ft_strlen((*varlist)->\
		varname)))
	{
		curr_var = (*varlist);
		*varlist = (*varlist)->next;
		free(curr_var->varname);
		free(curr_var->value);
		free(curr_var);
		return (2);
	}
	ft_unsetvar_b(varname, varlist);
	*varlist = head;
	return (1);
}
