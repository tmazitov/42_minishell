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

int ft_export(char *str, t_envlist **envlist, t_varlist **varlist, t_sorted_envlist *sorted_envlist)
{
	char				**var_split;
	int					index;

	index = 0;
	var_split = ft_split(str, ' ');
	if (ft_strncmp(var_split[index], "export", 6) > 0)
		return (free_pointer(var_split), 0);
	if (ft_strlen_dp(var_split) == 1)
		ft_printexport(sorted_envlist);
	while (var_split[++index] != NULL)
	{
		if (!ft_checkvarname(var_split[index]))
		{
			ft_printf("bash: export: '%s': not a valid identifier\n", var_split[index]);
			return (free_pointer(var_split), 0);
		}
		else
			ft_exportvar(var_split[index], envlist, varlist);
	}
	return (1);
}

void    ft_exportvar(char *varname, t_envlist **envlist, t_varlist **varlist)
{
	char		*varvalue;
	t_envlist	*curr_var;
	t_envlist	*env_head;
	t_varlist	*var_head;

	env_head = *envlist;
	var_head = *varlist;
	varvalue = ft_getenv(varname, *envlist, *varlist);
	ft_printf("varvalue: %s\n", varvalue);
	while (varvalue != NULL && (*envlist) != NULL)
	{
		if ((*envlist)->next == NULL)
		{
			curr_var = ft_create_env(varname, varvalue);
			(*envlist)->next = curr_var;
			break ;
		}
		*envlist = (*envlist)->next;
	}
	*envlist = env_head;
	*varlist = var_head;
}

t_sorted_envlist	*insertsortedlist(t_sorted_envlist *head, t_sorted_envlist *newnode)
{
	t_sorted_envlist	*curr_var;

	if (head == NULL || ft_strncmp(newnode->varname, head->varname, ft_strlen(newnode->varname) + ft_strlen(head->varname)) < 0)
	{
		newnode->next = head;
		return newnode;
	}
	curr_var = head;
	while (curr_var->next != NULL && ft_strncmp(newnode->varname, curr_var->next->varname, ft_strlen(newnode->varname) + ft_strlen(curr_var->next->varname)) > 0)
		curr_var = curr_var->next;
	newnode->next = curr_var->next;
	curr_var->next = newnode;
	return (head);
}

t_sorted_envlist    *ft_sortenvlist(t_sorted_envlist *sorted_envlist)
{
	t_sorted_envlist	*sortedlist;
	t_sorted_envlist	*curr_var;
	t_sorted_envlist	*next_var;

	sortedlist = NULL;
	curr_var = sorted_envlist;
	while (curr_var != NULL)
	{
		next_var = curr_var->next;
		sortedlist = insertsortedlist(sortedlist, curr_var);
		curr_var = next_var;
	}
	return (sortedlist);
}

void    ft_printexport(t_sorted_envlist *sorted_envlist)
{
	t_sorted_envlist *curr_var;

	curr_var = ft_sortenvlist(sorted_envlist);
	while (curr_var != NULL)
	{
		ft_printf("declare  -x  %s=\"%s\"\n", curr_var->varname, curr_var->value);
		curr_var = curr_var->next;
	}
}