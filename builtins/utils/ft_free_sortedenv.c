/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_sortedenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:30:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/26 18:40:45 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_free_sortedenv(t_sorted_envlist **sorted_envlist)
{
	t_sorted_envlist	*prev_sort;

	while (*sorted_envlist != NULL)
	{
		free((*sorted_envlist)->value);
		free((*sorted_envlist)->varname);
		prev_sort = *sorted_envlist;
		*sorted_envlist = (*sorted_envlist)->next;
		free(prev_sort);
	}
}
