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


int ft_builtins(char *str, char **envp)
{
    t_envlist *envlist;
    t_varlist *varlist;
    t_sorted_envlist *sorted_envlist;

    envlist = ft_init_env(envp);
	sorted_envlist = ft_init_sortedenv(envp);
	varlist = ft_init_var();
    if (ft_strncmp(str, "echo", 4) == 0)
        ft_echo(str, envlist, varlist);
    else if (ft_strchr(str, '=') && !ft_checkcmd(str))
        ft_setvarname(str, varlist);
    else if (ft_strncmp(str, "unset", 5) == 0)
        ft_unsetvarname(str, envlist, varlist);
    else if (ft_strncmp(str, "export", 6) == 0)
        ft_export(str, envlist, varlist, sorted_envlist);
    else if (ft_strncmp(str, "env", 3) == 0)
        ft_printenv(envlist);
    else
        return (1);
    return (1);
}

bool    ft_checkcmd(char *str)
{
    if (ft_strncmp(str, "echo", 4) == 0)
        return (true);
    else if (ft_strncmp(str, "unset", 5) == 0)
        return (true);
    else if (ft_strncmp(str, "export", 6) == 0)
        return (true);
    else if (ft_strncmp(str, "env", 3) == 0)
        return (true);
    else
        return (false);
}