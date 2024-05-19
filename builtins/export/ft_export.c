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

int	ft_export(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char				**var_split;
	int					index;

	index = 0;
	var_split = ft_split(str, ' ');
	// if (ft_strncmp("export", var_split[index], ft_strlen(var_split[index])))
	// 	return (free_pointer(var_split), 0);
	if (ft_strlen_dp(var_split) == 1)
		ft_printexport(envlist);
	while (var_split[++index] != NULL)
	{
		if (!ft_checkvarname(var_split[index]))
		{
			ft_printf("bash: export: '%s': not a valid identifier\n", \
				var_split[index]);
			return (free_pointer(var_split), 0);
		}
		else
			ft_exportvar(var_split[index], envlist, varlist);
	}
	return (free_pointer(var_split), 1);
}

void	ft_exportvar(char *varname, t_envlist **envlist, t_varlist **varlist)
{
	char		*varvalue;
	t_envlist	*curr_var;
	t_envlist	*env_head;
	t_varlist	*var_head;

	env_head = *envlist;
	var_head = *varlist;
	varvalue = ft_getenv(varname, *envlist, *varlist);
	while (varvalue != NULL && (*envlist) != NULL && \
		!ft_checkvarenv(varname, *envlist))
	{
		if ((*envlist)->next == NULL)
		{
			curr_var = ft_create_env(NULL, ft_strdup(varname), ft_strdup(varvalue));
			(*envlist)->next = curr_var;
			break ;
		}
		*envlist = (*envlist)->next;
	}
	*envlist = env_head;
	*varlist = var_head;
}

bool	ft_checkvarenv(char *varname, t_envlist *envlist)
{
	while (envlist != NULL && envlist->varname != NULL)
	{
		if (ft_strncmp(varname, envlist->varname, ft_strlen(varname)) == 0)
		{
			return (true);
		}
		else
			envlist = envlist->next;
	}
	return (false);
}
