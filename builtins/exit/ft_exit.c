/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:28:26 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/01 00:07:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_exit(char *str, t_envlist **envlist, t_varlist **varlist)
{
	free(str);
	ft_free_env(envlist);
	ft_free_var(varlist);
	exit (EXIT_SUCCESS);
}
