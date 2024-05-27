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
	char	*varname;
	t_varlist	*var_head;

	var_head = *varlist;
	index = 0;
	var = ft_splittoken(str);
	var = str_token(var);
	var = ft_handleexportsplit(str, var);
	if (ft_strlen_dp(var) == 1)
		ft_printexport(envlist, varlist);
	while (var[++index] != NULL)
	{
		varname = var[index];
		if (ft_strchr(varname, '=') && (ft_strlen(varname) > 1))
			varname = ft_splitequalsign(varname, ft_strchr(varname, '='), \
				envlist, varlist);
		if (ft_checkexport(varname, var[index], envlist, varlist) == 0)
			return (free_pointer(var), 0);
		if (ft_strchr(var[index], '=') && (ft_strlen(var[index]) > 1))
			free(varname);
	}
	*varlist = var_head;
	return (free_pointer(var), 1);
}

int	ft_checkexport(char *varname, char *str_input, t_envlist **envlist, \
	t_varlist **varlist)
{
	int	out;

	if ((!ft_strchr(str_input, '=') && !ft_checkvarlist(str_input, *varlist)) || \
		(ft_strchr(str_input, '=')))
	{
		if (!ft_strchr(str_input, '=') && !ft_checkvarlist(str_input, *varlist))
		{
			str_input = ft_mergevarval(NULL, ft_strdup(str_input), "=");
			out = ft_setvarname(str_input, envlist, varlist);
			free(str_input);
		}
		else
			out = ft_setvarname(str_input, envlist, varlist);
		if (out == 0 || !varname || (!ft_checkvarname(varname) && \
			!(ft_strchr(varname, '='))) || (varname[0] == '='))
			return (ft_printf("bash: export: '%s': not a valid identifier\n", \
					varname), 0);
	}
	if (!ft_checkvarenv(varname, *envlist))
		ft_exportvar(varname, envlist, varlist);
	return (1);
}

char	**ft_handleexportsplit(char *str, char **var)
{
	char	**out;
	int		count;
	int		index;

	out = (char **)malloc(sizeof(char *) * 1);
	out[0] = NULL;
	count = 0;
	index = -1;
	while (var[count] != NULL)
	{
		if ((count > 0) && (var[count][0] != '\"' || \
			var[count][0] != '\'') && ((size_t)(ft_strstr(str, var[count]) - \
			ft_strstr(str, var[count - 1])) == ft_strlen(var[count - 1])))
		{
			out[index] = ft_mergevarval(str, out[index], var[count]);
			str = ft_strstr(str, var[count++]);
		}
		else
		{
			index++;
			out = ft_realloc_dp(out, var[count++], ft_strlen_dp(out) + 1);
		}
	}
	free(var);
	return (out);
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
	while ((*envlist) != NULL)
	{
		if ((*envlist)->next == NULL)
		{
			curr_var = ft_create_env(NULL, ft_strdup(varname), \
				ft_strdup(varvalue));
			(*envlist)->next = curr_var;
			break ;
		}
		*envlist = (*envlist)->next;
	}
	if ((*envlist) == NULL)
		(*envlist) = ft_create_env(NULL, ft_strdup(varname), \
				ft_strdup(varvalue));
	else
		*envlist = env_head;
	*varlist = var_head;
}

bool	ft_checkvarenv(char *varname, t_envlist *envlist)
{
	while (envlist != NULL && envlist->varname != NULL)
	{
		if ((ft_strncmp(varname, envlist->varname, \
			ft_strlen(envlist->varname)) == 0) && (ft_strlen(envlist->varname) == ft_strlen(varname)))
		{
			return (true);
		}
		else
			envlist = envlist->next;
	}
	return (false);
}

bool	ft_checkvarlist(char *varname, t_varlist *varlist)
{
	while (varlist != NULL && varlist->varname != NULL)
	{
		if ((ft_strncmp(varname, varlist->varname, \
			ft_strlen(varlist->varname)) == 0) && (ft_strlen(varlist->varname) == ft_strlen(varname)))
		{
			return (true);
		}
		else
			varlist = varlist->next;
	}
	return (false);
}
