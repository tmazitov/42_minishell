/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:22:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/14 15:43:01 by emaravil         ###   ########.fr       */
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
		ft_openshfile(user_input);
		free(user_input);
	}
	else
	{
		root = parse_input(user_input);
		root = ft_setroot(&root, *envlist, *varlist);
		free(user_input);
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

	out = *rootnode;
	info.env = &envlist;
	info.var = &varlist;
	ft_checkdollar(rootnode, &info);
	*rootnode = out;
	ft_printf("\n----------------- SET ROOTPRINT AST ---------------\n");
	print_ast(*rootnode, 0);
	ft_printf("-----------------------------------------------------\n");
	return (out);
}

void	ft_checkdollar(t_astnodes **rootnode, t_builtin_info *info)
{
	if ((*rootnode) == NULL)
		return ;
	if (!((*rootnode)->left) && !((*rootnode)->right))
	{
		(*rootnode)->value = ft_expanddollar((*rootnode)->value, info);
		ft_printf("(*rootnode)->value %s\n", (*rootnode)->value);
		(*rootnode)->value = ft_cleanvalue((*rootnode)->value);
		ft_printf("(*rootnode)->value %s\n", (*rootnode)->value);
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
		// if (str[len] != '\"' && str[len] != '\'')
		out[len - index] = str[len];
		// else
		// 	index++;
		len++;
	}
	out[len] = '\0';
	free(str_temp);
	return (out);
}
