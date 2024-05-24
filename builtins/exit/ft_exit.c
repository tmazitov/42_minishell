/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:28:26 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/24 03:31:15 by marvin           ###   ########.fr       */
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
	while (str_split[1] != NULL && str_split[1][count])
	{
		if (ft_isdigit(str_split[1][count]) == 0)
		{
			ft_printf("bash: exit: %s: numeric argument required\n", \
				str_split[1]);
			break;
		}
		count++;
	}
	free_pointer(str_split);
	free(str);
	ft_free_env(envlist);
	ft_free_var(varlist);
	exit (EXIT_SUCCESS);
}
