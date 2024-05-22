/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:10:51 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/22 13:07:03 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_printenv(t_envlist *envlist, t_varlist *varlist)
{
	while (envlist != NULL && envlist->varname != NULL)
	{
		if (!(ft_checkvarlist(envlist->varname, varlist) && !*(envlist->value)))
		{
			ft_printf("%s", envlist->varname);
			ft_printf("=%s", envlist->value);
			ft_printf("\n");
		}
		envlist = envlist->next;
	}
}
