/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:28:26 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/05 20:02:43 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_exit(char *str, t_builtin_info *info)
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
	free_queue(info->q);
	ft_free_env(info->env);
	ft_free_var(info->var);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit (EXIT_SUCCESS);
}
