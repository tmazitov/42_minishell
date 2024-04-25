/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:20:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/25 22:04:22 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_pwd()
{
	char	*path;

	path = getenv("PWD");
	ft_printf("%s\n", path);
	// while ((envlist) != NULL && (envlist->varname) != NULL)
	// {
	// 	if (ft_strncmp(envlist->varname, "pwd", 3) == 0 || \
	// 		ft_strncmp(envlist->varname, "PWD", 3) == 0)
	// 	{
	// 		ft_printf("%s\n", envlist->value);
	// 		break ;
	// 	}
	// 	envlist = envlist->next;
	// }
}
