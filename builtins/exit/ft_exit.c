/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:28:26 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/22 13:20:14 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_exit(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	**str_split;
	int		count;

	count = 0;
	str_split = ft_split(str, ' ');
	ft_printf("exit\n");
	while (str_split[1][count])
	{
		if (ft_isdigit(str_split[1][count]) == 0)
		{
			ft_printf("bash: exit: %s: numeric argument required\n", str_split[1]);
			break;
		}
		count++;
	}
	free(str);
	ft_free_env(envlist);
	ft_free_var(varlist);
	exit (EXIT_SUCCESS);
}
