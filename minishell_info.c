/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:00:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 21:10:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*prepare_env(t_envlist **env, t_varlist **varlist, char **envp)
{
	*env = ft_init_env(envp);
	ft_cd(NULL, env, varlist);
	ft_mergedollar_b(NULL, NULL, *env, *varlist);
	return (*env);
}

t_varlist	*prepare_var(t_varlist **var)
{
	return ((*var = ft_init_var()));
}

void	graceful_finish(t_envlist **env, t_varlist **var)
{
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	ft_free_env(env);
	ft_free_var(var);
}
