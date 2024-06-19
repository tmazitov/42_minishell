/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:10:51 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 05:46:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_printenv(t_envlist *envlist, t_varlist *varlist)
{
	while (envlist != NULL && envlist->varname != NULL)
	{
		if (!(ft_checkvarlist(envlist->varname, varlist) && !(envlist->value)))
		{
			ft_printf("%s", envlist->varname);
			ft_printf("=%s", envlist->value);
			ft_printf("\n");
		}
		envlist = envlist->next;
	}
}
