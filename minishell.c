/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/25 04:28:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	int				status;
	t_astnodes		*root;
    t_envlist		*envlist;
    t_varlist		*varlist;
    t_sorted_envlist *sorted_envlist;

	(void)argc;
	(void)argv;
    envlist = ft_init_env(envp);
	sorted_envlist = ft_init_sortedenv(envp);
	varlist = ft_init_var();
	while (1)
	{
		str = readline("\033[1;32mminishell$\033[0m ");
		while (ft_isspace(*str) > 0)
			str++;
		if (ft_strlen(str) > 0 && *str != '\0')
		{
			add_history(str);
			if (ft_checkshfile(str))
				ft_openshfile(str);
			else
			{
				root = parse_input(str);
				ft_builtins(str, &envlist, &varlist, &sorted_envlist);
				if (root)
				{
					status = execute(root, envp);
					if (status < 0)
						ft_printf("execution error : status code %d\n", status);
					else
						ft_printf("success execution : status code %d\n", status);
				}
			}
			// free(str); //cannot free . if str is space, the error would be (free(): invalid pointer zsh: IOT instruction ./minishell)
		}
	}
	return (0);
}
