/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/25 17:23:18 by tmazitov         ###   ########.fr       */
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
	setup_read_interrupter();
	status_code(SET, 0);
	while (1)
	{
		ft_printf("\033[1;32mminishell$\033[0m ");
		str = get_next_line(STDIN_FILENO);
		if (str)
			status_code(SET, 0);
		if (!str && status_code(GET, -1) == 130)
		{
			status_code(SET, 0);
			continue;
		}
		if (!str)
			return (1);
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
					if (status >= 0)
						ft_printf("success execution : status code %d\n", status);
					else if (status_code(GET, -1))
						ft_printf("success execution : status code %d\n", status_code(GET, -1));
					else
						ft_printf("execution error : status code %d\n", status);
				}
			}
			// free(str); //cannot free . if str is space, the error would be (free(): invalid pointer zsh: IOT instruction ./minishell)
		}
	}
	return (0);
}
