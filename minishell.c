/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:01 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/24 17:39:44 by marvin           ###   ########.fr       */
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
			while (ft_isspace(*str) > 0)
				str++;
			if (ft_checkshfile(str))
				ft_openshfile(str);
			else
			{
				root = parse_input(str);
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

void	ft_printenvp(char **envp)
{
	int	count;
	char *result;
	char **varname;

	count = 0;
	varname = ft_split(envp[0], '=');
	envp[0] = "eli";
	result = getenv(varname[0]);
	ft_printf("%s\n", result);
	ft_printf("%s\n", *envp);
	while (envp[count] != NULL)
	{
		ft_printf("envp: %s\n", envp[count]);
		count++;
	}
}