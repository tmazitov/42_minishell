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

// int	ft_builtins(char *str, t_envlist **envlist, t_varlist **varlist)
int	ft_builtins(char *str, t_builtin_info *info)
{
	t_envlist	*env_head;
	// t_varlist	*var_head;

	env_head = NULL;
	if ((*info->env) != NULL)
		env_head = *info->env;
	// var_head = *varlist;
	if (ft_strncmp(str, "echo", 4) == 0)
		ft_echo(str, *info->env, *info->var);
	else if (ft_strchr(str, '=') && !ft_checkcmd(str))
		ft_setvar(str, info->env, info->var);
	else if (ft_strncmp(str, "unset", 5) == 0)
		ft_unsetvarname(str, info->env, info->var);
	else if (ft_strncmp(str, "export", 6) == 0)
		ft_export(str, info->env, info->var);
	else if (ft_strncmp(str, "env", 3) == 0)
		ft_printenv(*info->env, *info->var);
	else if (ft_strncmp(str, "cd", 2) == 0)
		ft_cd(str, info->env, info->var);
	else if (ft_strncmp(str, "pwd", 3) == 0 || (ft_strncmp(str, "PWD", 3) == 0))
		ft_pwd(str);
	else if (ft_strncmp(str, "exit", 4) == 0)
		ft_exit(str, info);
	else if (ft_strncmp(str, "varrr", 5) == 0)
		ft_printvar(info->var);
	else
		ft_printf("HANDLE THIS IF NOT IN BUUILTIN '%s'\n", str);
	if (env_head != NULL)
		*info->env = env_head;
	// *varlist = var_head;
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
