/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:30:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/30 16:00:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_free_var(t_varlist **varlist)
{
	t_varlist	*prev;

	while (*varlist != NULL)
	{
		free((*varlist)->value);
		free((*varlist)->varname);
		prev = *varlist;
		(*varlist) = (*varlist)->next;
		free(prev);
	}
}
