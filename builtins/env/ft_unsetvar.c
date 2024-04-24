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

int	ft_unsetvarname(char *str, t_envlist *envlist, t_varlist *varlist)
{
	char	**var_split;
	int		result;
	int		count;

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
		if (!ft_checkvarname(var_split[count]))
		{
			ft_printf("unset: %s: invalid parameter name\n", var_split[count]);
			return (free_pointer(var_split), 0);
		}
		result *= ft_unsetenv(var_split[count], envlist, varlist);
		count++;
	}
	return (free_pointer(var_split), result);
}

int	ft_unsetenv(char *varname, t_envlist *envlist, t_varlist *varlist)
{
	t_envlist	*curr_env;
	t_envlist	*prev_env;
	int			result;

	result = 0;
	prev_env = NULL;
	curr_env = envlist;
	while (curr_env != NULL && ft_strncmp(varname, curr_env->varname, ft_strlen(varname)) > 0)
	{
		prev_env = curr_env;
		curr_env = curr_env->next;
	}
	if (prev_env == NULL)
		varlist = curr_env->next;
	else if (curr_env != NULL)
	{
		prev_env->next = curr_env->next;
		free(curr_env);
	}
	else
		return (ft_unsetvar(varname, varlist) || 0);
	return (ft_unsetvar(varname, varlist) || 1);
}

int	ft_unsetvar(char *varname, t_varlist *varlist)
{
	t_varlist	*curr_var;
	t_varlist	*prev_var;

	prev_var = NULL;
	curr_var = varlist;
	while (curr_var != NULL && ft_strncmp(varname, curr_var->varname, ft_strlen(varname)) > 0)
	{
		prev_var = curr_var;
		curr_var = curr_var->next;
	}
	if (prev_var == NULL)
		varlist = curr_var->next;
	else if (curr_var != NULL)
	{
		prev_var->next = curr_var->next;
		free(curr_var);
	}
	else
		return (0);
	return (1);
}