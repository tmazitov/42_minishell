/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:30:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/26 18:35:34 by emaravil         ###   ########.fr       */
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
