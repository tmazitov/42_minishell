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
	char	**var;
	int		index;
	int		out;
	char	*varname;

	index = 0;
	out = 1;
	var = ft_split(str, ' ');
	if (ft_strlen_dp(var) == 1)
		ft_printexport(envlist);
	while (var[++index] != NULL) 
	{
		varname = var[index];
		if (ft_strchr(var[index], '='))
		{
			varname = ft_splitequalsign(varname, ft_strchr(varname, '='), \
				envlist, varlist);
			out = ft_setvarname(var[index], envlist, varlist);
		}
		if (ft_checkexport(varname, out, envlist, varlist) == 0)
			return (free_pointer(var), 0);
	}
	return (free_pointer(var), 1);
}

int	ft_checkexport(char *varname, int out, t_envlist **envlist, t_varlist **varlist)
{
	if (out == 0 || !varname || (!ft_checkvarname(varname) && \
		!(ft_strchr(varname, '='))))
		return (ft_printf("bash: export: '%s': not a valid identifier\n", \
				varname), 0);
	else
		ft_exportvar(varname, envlist, varlist);
	return (1);
}

// char	*ft_splittoname(char *str, t_envlist **envlist, t_varlist **varlist)
// {
// 	char		*varname;
// 	char		*varvalue;
// 	t_varlist	*var_head;

// 	var_head = *varlist;
// 	varvalue = NULL;
// 	if (ft_strchr(str, '='))
// 	{
// 		varname = ft_splitequalsign(str, ft_strchr(str, '='), envlist, varlist);
// 		varvalue = ft_splitequalsign((ft_strchr(str,'=')), 
// 			ft_strchr(str, '\0'), envlist, varlist);
// 	}
// 	else
// 		varname = str;
// 	if (!varname || !ft_checkvarname(varname))
// 	{
// 		if (varname)
// 			free(varname);
// 		if (varvalue)
// 			free(varvalue);
// 		return (ft_printf("bash: export: '%s': not a valid identifier\n", 
// 			varname), NULL);
// 	}
// 	else
// 		ft_setenv(varname, varvalue, 1, varlist);
// 	*varlist = var_head;
// 	return (varname);
// }


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
