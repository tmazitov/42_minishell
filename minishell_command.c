/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:22:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/09 23:42:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	user_input_is_valid(char *user_input)
{
	return ((bool)(user_input 
		&& ft_strlen(user_input) > 0 
		&& *user_input != '\0'));
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
		ft_printf("root->value |%s|\n", root->value);
		execute(&root, envlist, varlist);
		if (root)
			ft_free_ast(root);
	}
}

t_astnodes	*ft_setroot(t_astnodes **rootnode, t_envlist *envlist, \
	t_varlist *varlist)
{
	t_astnodes	*out;

	out = *rootnode;
	ft_checkdollar(rootnode, envlist, varlist);
	*rootnode = out;
	ft_printf("\n----------------- SET ROOTPRINT AST ---------------\n");
	print_ast(*rootnode, 0);
	ft_printf("-----------------------------------------------------\n");
	return (out);
}

void	ft_checkdollar(t_astnodes **rootnode, t_envlist *envlist, \
	t_varlist *varlist)
{
	if ((*rootnode) == NULL)
		return ;
	if (!((*rootnode)->left) && !((*rootnode)->right))
	{
		(*rootnode)->value = ft_expanddollar((*rootnode)->value, envlist, varlist);
		(*rootnode)->value = ft_cleanvalue((*rootnode)->value);
	}
	ft_checkdollar(&(*rootnode)->left, envlist, varlist);
	ft_checkdollar(&(*rootnode)->right, envlist, varlist);
}

char	*ft_cleanvalue(char *str)
{
	size_t	len;
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
	while (str[len] != '\0' && str[len] != '\n')
	{
		out[len] = str[len];
		len++;
	}
	out[len] = '\0';
	free(str_temp);
	return (out);
}

char	*ft_expanddollar(char *str, t_envlist *envlist, t_varlist *varlist)
{
	char	*varname;
	int		count;
	char	*out;
	int		mode;
	char	*str_temp;

	out = (char *)ft_calloc(1, sizeof(char));
	if (out == NULL)
		return (NULL);
	count = 0;
	mode = 1;
	while (str[count])
	{
		mode = ft_selectmode(str[count], mode);
		if (str[count] == '$' && mode == 1)
		{
			if (str[count + 1] == '?')
			{
				str_temp = ft_itoa(status_code(GET_HISTORY, -1));
				out = ft_mergevarval(NULL, out, str_temp);
				free(str_temp);
				count += 2;
			}
			else if ((((str[count + 1]) == '\0') || (ft_isspace(str[count + 1]) > 0) || (str[count + 1] != '\"')) && !(((ft_isdigit(str[count + 1]) > 0) || \
					((ft_isalpha(str[count + 1]) > 0)) || str[count + 1] == '_')))
			{
				out = ft_mergevarval(NULL, out, "$");
				count++;
			}
			else if ((ft_isspace(str[count + 1]) == 0) && (str[count + 1] != '\"') && ((ft_isdigit(str[count + 1]) > 0) || \
					((ft_isalpha(str[count + 1]) > 0)) || str[count + 1] == '_'))
			{
				varname = ft_getvarname(str, ++count);
				if (!varname)
					count += ft_countvarname(&str[count]);
				else
				{
					out = ft_mergedollar_b(varname, out, envlist, varlist);
					count += ft_countvarname(&str[count]);
				}
				free(varname);
			}
		}
		else
			out = ft_mergedollar_a(str, out, count++);
	}
	free(str);
	return (out);
}

int	ft_selectmode(char c, int mode)
{
	if (c == '\'' && mode == 1)
		mode = 0;
	else if (c == '\'' && mode == 0)
		mode = 1;
	return (mode);
}

char	*ft_mergedollar_a(char *str, char *out, int count)
{
	size_t	outlen;

	out = ft_realloc(out, ft_strlen(out) + 2);
	outlen = ft_strlen(out);
	out[outlen] = str[count];
	out[outlen + 1] = '\0';
	return (out);
}

char	*ft_mergedollar_b(char	*varname, char *out, t_envlist *envlist, \
	t_varlist *varlist)
{
	char	*varvalue;

	varvalue = ft_getenv(varname, envlist, varlist);
	if (varvalue != NULL && *varvalue)
		out = ft_mergevarval(NULL, out, varvalue);
	return (out);
}
