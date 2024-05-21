/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:10:51 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/18 23:06:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_printenv(t_envlist *envlist)
{
	while (envlist != NULL && envlist->varname != NULL)
	{
		ft_printf("%s=", envlist->varname);
		ft_printf("%s\n", envlist->value);
		envlist = envlist->next;
	}
}
