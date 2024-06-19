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

int	ft_builtins(char *str, t_builtin_info *info)
{
	t_envlist	*env_head;
	int			exit_status;

	exit_status = 0;
	env_head = NULL;
	if ((*info->env) != NULL)
		env_head = *info->env;
	if (ft_compname("echo", str))
		ft_echo(str, *info->env, *info->var);
	else if (ft_strchr(str, '=') && !ft_checkcmd(str))
		exit_status = ft_setvar(str, info->env, info->var);
	else if (ft_compname("unset", str))
		exit_status = ft_unsetvarname(str, info->env, info->var);
	else if (ft_compname("cd", str))
		exit_status = ft_cd(str, info->env, info->var);
	else
		exit_status = ft_builtins_b(str, info);
	if (env_head != NULL)
		*info->env = env_head;
	return (exit_status);
}

int	ft_builtins_b(char	*str, t_builtin_info *info)
{
	int		exit_status;

	exit_status = 0;
	if (ft_compname("env", str))
		ft_printenv(*info->env, *info->var);
	else if (ft_compname("pwd", str) || ft_compname("PWD", str))
		ft_pwd(str);
	else if (ft_compname("exit", str))
		exit_status = ft_exit(str, info);
	else if (ft_compname("varrr", str))
		ft_printvar(info->var);
	else if (ft_compname("export", str))
		exit_status = ft_export(str, info->env, info->var);
	return (exit_status);
}

bool	ft_compname(char *str1, char *str2)
{
	char	**out;

	if (!str1 || !str2)
		return (NULL);
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
	value = ft_strdup(ft_getenv(varname, envlist, varlist));
	if (value == NULL)
		return ;
	free(value);
}

bool	ft_checkcmd(char *str)
{
	if (ft_compname("echo", str))
		return (true);
	else if (ft_compname("unset", str))
		return (true);
	else if (ft_compname("export", str))
		return (true);
	else if (ft_compname("env", str))
		return (true);
	else if (ft_compname("cd", str))
		return (true);
	else if (ft_compname("exit", str))
		return (true);
	else if (ft_compname("varrr", str))
		return (true);
	else if (ft_compname("pwd", str) || ft_compname("PWD", str))
		return (true);
	else
		return (false);
}
