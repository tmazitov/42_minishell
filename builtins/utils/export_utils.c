/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:16:53 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/21 23:33:55 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

t_sorted_envlist	*insertsortedlist(t_sorted_envlist *head, \
	t_sorted_envlist *newnode)
{
	t_sorted_envlist	*curr_var;

	if (head == NULL || ft_strncmp(newnode->varname, head->varname, \
		ft_strlen(newnode->varname) + ft_strlen(head->varname)) < 0)
	{
		newnode->next = head;
		return (newnode);
	}
	curr_var = head;
	while (curr_var->next != NULL && ft_strncmp(newnode->varname, \
		curr_var->next->varname, ft_strlen(newnode->varname) + \
		ft_strlen(curr_var->next->varname)) > 0)
		curr_var = curr_var->next;
	newnode->next = curr_var->next;
	curr_var->next = newnode;
	return (head);
}

t_sorted_envlist	*ft_sortenvlist(t_sorted_envlist *sorted_envlist)
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

t_sorted_envlist	*ft_init_sortedenv(t_envlist **envlist)
{
	t_sorted_envlist	*var;
	t_sorted_envlist	*curr_var;
	t_sorted_envlist	*sorted_envlist;

	if (!*envlist)
		return (NULL);
	var = ft_create_sortedenv((*envlist)->varname, (*envlist)->value);
	sorted_envlist = var;
	while ((*envlist) != NULL && (*envlist)->varname != NULL)
	{
		curr_var = ft_create_sortedenv((*envlist)->varname, (*envlist)->value);
		(*envlist) = (*envlist)->next;
		var->next = curr_var;
		var = var->next;
	}
	return (sorted_envlist);
}

void	ft_printexport(t_envlist **envlist, t_varlist **varlist)
{
	t_sorted_envlist	*curr_var;
	t_sorted_envlist	*sorted_envlist;
	t_varlist			*var_head;

	sorted_envlist = ft_init_sortedenv(envlist);
	sorted_envlist = ft_sortenvlist(sorted_envlist);
	curr_var = sorted_envlist;
	while (curr_var != NULL)
	{
		ft_printf("declare  -x  %s=\"%s\"\n", \
			curr_var->varname, curr_var->value);
		curr_var = curr_var->next;
	}
	var_head = *varlist;
	while (*varlist != NULL && (*varlist)->varname != NULL)
	{
		ft_printf("declare  -x  %s", (*varlist)->varname);
		if ((*varlist)->value)
			ft_printf("=\"%s\"\n", (*varlist)->value);
		else
			ft_printf("\n");
		(*varlist) = (*varlist)->next;
	}
	*varlist = var_head;
	ft_free_sortedenv(&sorted_envlist);
}
