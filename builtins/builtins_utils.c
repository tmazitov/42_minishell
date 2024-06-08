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
	if (ft_compname("echo", str))
		ft_echo(str, *info->env, *info->var);
	else if (ft_strchr(str, '=') && !ft_checkcmd(str))
		ft_setvar(str, info->env, info->var);
	else if (ft_compname("unset", str))
		ft_unsetvarname(str, info->env, info->var);
	else if (ft_compname("export", str))
		ft_export(str, info->env, info->var);
	else if (ft_compname("env", str))
		ft_printenv(*info->env, *info->var);
	else if (ft_compname("cd", str))
		ft_cd(str, info->env, info->var);
	else if (ft_compname("pwd", str) || ft_compname("PWD", str))
		ft_pwd(str);
	else if (ft_compname("exit", str))
		ft_exit(str, info);
	else if (ft_compname("varrr", str))
		ft_printvar(info->var);
	else if (str[0] == '$')
		ft_handle_dollar(str, *info->env, *info->var);
	if (env_head != NULL)
		*info->env = env_head;
	return (0);
}

bool	ft_compname(char *str1, char *str2)
{
	char	**out;

	out = ft_split(str2, ' ');
	if (ft_strncmp(str1, out[0], ft_strlen(out[0])) == 0 && \
		(ft_strlen(str1) == ft_strlen(out[0])))
		return (free_pointer(out), true);
	else
		return (free_pointer(out), false);
}

void	ft_handle_dollar(char *str, t_envlist *envlist, t_varlist *varlist)
{
	char	*varname;
	char	*value;

	varname = ft_getvarname(str, 1);
	if (varname == NULL)
		return ;
	value = ft_getenv(varname, envlist, varlist);
	ft_printf("varnaEme: %s value: %s\n", varname, value);
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
