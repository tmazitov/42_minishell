/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:22:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/04 14:05:46 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



bool	user_input_is_valid(char *user_input) 
{
	return ((bool)(user_input && ft_strlen(user_input) > 0 && *user_input != '\0'));
}

bool	is_sh_file(char *user_input)
{
	return ((bool)ft_checkshfile(user_input));
}

bool	is_single_command(int argc, char **argv)
{
	return ((bool)(argc == 3 
			&& argv[1] != NULL 
			&& ft_strncmp("-c", argv[1], 3) == 0)
			&& argv[2] != NULL
			&& ft_strlen(argv[2]) > 0);
}

void	different_execute(char *user_input, t_envlist **envlist, t_varlist **varlist)
{
	t_astnodes		*root;

	if (is_sh_file(user_input))
	{
		ft_openshfile(user_input);
		free(user_input);		
	}
	else
	{
		root = parse_input(user_input);
		free(user_input);
		if (!root)
			return ;
		execute(&root, envlist, varlist);
		if (root)
			ft_free_ast(root);
	}
}