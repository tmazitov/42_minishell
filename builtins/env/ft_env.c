/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:10:51 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/25 22:11:17 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_printenv(t_envlist *envlist)
{
	while (envlist != NULL)
	{
		ft_printf("%s=%s\n", envlist->varname, envlist->value);
		envlist = envlist->next;
	}
}
