/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/26 13:26:07 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str; //str input
	int				status;
	t_astnodes		*root;
    t_envlist		*envlist;
    t_varlist		*varlist;
    // t_sorted_envlist *sorted_envlist;

	(void)argc;
	(void)argv;
    envlist = ft_init_env(envp);
	// sorted_envlist = ft_init_sortedenv(envp);
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
				ft_builtins(str, &envlist, &varlist);
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
