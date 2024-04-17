/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 02:12:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	int			status;
	t_astnodes	*root;

	(void)argc;
	(void)argv;

	while (1)
	{
		str = readline("\033[1;32mminishell$\033[0m ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			if (ft_checkshfile(str))
				ft_openshfile(str);
			else {
				root = parse_input(str);
				if (!root) {
					free(str);
					continue ;
				}
				status = execute(root, envp);
				if (status < 0)
					ft_printf("execution error : status code %d\n", status);
				else
					ft_printf("success execution : status code %d\n", status);
			}
			free(str);
		}
	}
	return (0);
}
