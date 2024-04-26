/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:30:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/26 18:43:31 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_free_env(t_envlist **envlist)
{
	t_envlist			*prev;

	while (*envlist != NULL)
	{
		free((*envlist)->value);
		free((*envlist)->varname);
		prev = *envlist;
		*envlist = (*envlist)->next;
		free(prev);
	}
}
