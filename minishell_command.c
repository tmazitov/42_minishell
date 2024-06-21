/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:22:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/21 21:44:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_single_command(int argc, char **argv)
{
	return ((bool)(argc == 3
		&& argv[1] != NULL
		&& ft_strncmp("-c", argv[1], 3) == 0)
		&& argv[2] != NULL
		&& ft_strlen(argv[2]) > 0);
}

void	different_execute(char *user_input, t_envlist **envlist, \
							t_varlist **varlist)
{
	t_astnodes		*root;

	if (is_sh_file(user_input))
	{
		ft_err_p("Error: sh file not allowed!\n", NULL, NULL);
		free(user_input);
	}
	else
	{
		root = parse_input(user_input);
		free(user_input);
		if (!root)
		{
			status_code(SET, 258);
			return ;
		}
		root = ft_setroot(&root, *envlist, *varlist);
		if (!root)
			return ;
		execute(&root, envlist, varlist);
		if (root)
			ft_free_ast(root);
	}
}

t_astnodes	*ft_setroot(t_astnodes **rootnode, t_envlist *envlist, \
	t_varlist *varlist)
{
	t_astnodes		*out;
	t_builtin_info	info;
	char			*str_temp;

	out = *rootnode;
	info.env = &envlist;
	info.var = &varlist;
	str_temp = NULL;
	ft_checkdollar(rootnode, &info);
	if (!((*rootnode)->left) && !((*rootnode)->right) && \
		(ft_strchr((*rootnode)->value, '|') && \
		ft_strlen((*rootnode)->value) > 0))
	{
		str_temp = ft_strdup((*rootnode)->value);
		ft_free_ast(*rootnode);
		out = parse_input(str_temp);
		free(str_temp);
		if (out == NULL)
		{
			status_code(SET, 258);
			return (NULL);
		}
	}
	*rootnode = out;
	return (out);
}

void	ft_checkdollar(t_astnodes **rootnode, t_builtin_info *info)
{
	if ((*rootnode) == NULL)
		return ;
	if (!((*rootnode)->left) && !((*rootnode)->right))
	{
		(*rootnode)->value = ft_expanddollar((*rootnode)->value, info);
		(*rootnode)->value = ft_cleanvalue((*rootnode)->value);
		if (!ft_checkcmd((*rootnode)->value) && !((ft_strchr(\
			(*rootnode)->value, '=') && !ft_checkcmd((*rootnode)->value))))
			(*rootnode)->value = ft_cdcleanvalue((*rootnode)->value);
	}
	ft_checkdollar(&(*rootnode)->left, info);
	ft_checkdollar(&(*rootnode)->right, info);
}

char	*ft_cleanvalue(char *str)
{
	size_t	len;
	size_t	index;
	char	*out;
	char	*str_temp;

	str_temp = str;
	len = 0;
	while (ft_isspace(*str) > 0)
		str++;
	out = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!out)
		return (NULL);
	ft_bzero(out, ft_strlen(str) + 1);
	index = 0;
	while (str[len] != '\0' && str[len] != '\n')
	{
		out[len - index] = str[len];
		len++;
	}
	out[len] = '\0';
	free(str_temp);
	return (out);
}
