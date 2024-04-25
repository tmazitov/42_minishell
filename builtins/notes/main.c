/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkgrammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:08 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 18:35:51 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	main(int argc, char **argv, char **envp)
{
	char		**argv_split;
	char		var_echo[10];
	t_envlist			*envlist; // global variable. this should be declared at the main function of minishell
	t_varlist			*varlist; // global variable. this should be declared at the main function of minishell
	t_sorted_envlist	*sorted_envlist;

	if (argc != 2)
		return 0;
	ft_strlcpy(var_echo, "echo $", 7);
	envlist = ft_init_env(envp);
	// sorted_envlist = ft_init_sortedenv(envp);
	varlist = ft_init_var();
	argv_split = ft_split(argv[1], ' ');
	if (ft_strchr(argv_split[0], '='))
	{
		ft_printvar(varlist);
		ft_setvarname(argv_split[0], varlist);
		ft_printvar(varlist);
	}
	else if (ft_strncmp(argv_split[0], "echo", 4) == 0)
	{
		ft_echo(argv[1], envlist, varlist);
	}
	else if (ft_strncmp(argv_split[0], "unset", 5) == 0)
	{
		ft_printvar(varlist);
		ft_unsetvarname(argv[1], envlist, varlist);
		ft_printvar(varlist);
	}
	else if (ft_strncmp(argv_split[0], "export", 6) == 0)
	{
		ft_export(argv[1], envlist, varlist, sorted_envlist);
	}
	else if (ft_strncmp(argv_split[0], "env", 3) == 0)
	{
		ft_printenv(envlist);
	}
	return (0);
}

	// char *var_echo;

	// ft_strlcpy(var_echo, argv[1], 4);
	// ft_printf("argv[1]: %s\n", argv[1]);
	// if (ft_strchr(argv[1], '='))
	// 	ft_setvar(argv[1]);
	// else if (ft_strncmp("echo", var_echo, 4))
	// 	ft_echo(argv[1]);
	// return (0);
