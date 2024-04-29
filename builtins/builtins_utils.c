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

int	ft_builtins(char *str, t_envlist **envlist, t_varlist **varlist)
{
	t_envlist			*env_head;

	env_head = *envlist;
	ft_printf("\n###### BUILTIN COMMANDS #######\n");
	if (ft_strncmp(str, "echo", 4) == 0)
		ft_echo(str, *envlist, *varlist);
	else if (ft_strchr(str, '=') && !ft_checkcmd(str))
		ft_setvarname(str, varlist);
	else if (ft_strncmp(str, "unset", 5) == 0)
		ft_unsetvarname(str, envlist, varlist);
	else if (ft_strncmp(str, "export", 6) == 0)
		ft_export(str, envlist, varlist);
	else if (ft_strncmp(str, "env", 3) == 0)
		ft_printenv(*envlist);
	else if (ft_strncmp(str, "cd", 2) == 0)
		ft_cd(str, envlist, varlist);
	else if (ft_strncmp(str, "pwd", 3) == 0 || (ft_strncmp(str, "PWD", 3) == 0))
		ft_pwd();
	else if (ft_strncmp(str, "exit", 4) == 0)
		ft_exit(str, envlist, varlist);
	else if (ft_strncmp(str, "varrr", 5) == 0)
		ft_printvar(varlist);
	ft_printf("###### BUILTIN COMMANDS #######\n\n");
	*envlist = env_head;
	return (0);
}

bool	ft_checkcmd(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "varrr", 5) == 0)
		return (true);
	else if (ft_strncmp(str, "pwd", 3) == 0 || (ft_strncmp(str, "PWD", 3) == 0))
		return (true);
	else
		return (false);
}
