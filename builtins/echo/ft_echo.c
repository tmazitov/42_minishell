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

#include "../builtins.h"

/// @brief ft_echo handles the string with echo as command and multiple arguments
/// @param str string in format "echo arg1 arg2 arg3 ..."
void	ft_echo(char *str, t_envlist *envlist, t_varlist *varlist)
{
	char	**cmd_split;

	cmd_split = ft_splittoken(str);
	if (!cmd_split)
		return ;
	cmd_split = str_token(cmd_split);
	ft_printparams(cmd_split, envlist, varlist);
	free_pointer(cmd_split);
}

/// @brief print the arguments of echo
/// @param cmd_split double pointer from ft_split from echo string excluding quotes
void	ft_printparams(char **cmd_split, t_envlist *envlist, t_varlist *varlist)
{
	int	len;

	len = 1;
	while (cmd_split[len] != NULL)
	{
		if (cmd_split[len][0] == '\'')
			ft_printsquotes(cmd_split[len]);
		else if (cmd_split[len][0] == '$')
			ft_printexpansion(cmd_split[len], 1, envlist, varlist);
		else if (cmd_split[len][0] == '\"')
			ft_printdquotes(cmd_split[len], envlist, varlist);
		else
			ft_printf("%s", cmd_split[len]);
		len++;
		if (cmd_split[len] != NULL)
			ft_printf(" ");
	}
	ft_printf("\n");
}

/// @brief expand the $var and get it's value. Otherwise print it as string
/// @param str string with $ sign
/// @param index next index of the index of $ sign
void	ft_printexpansion(char *str, int index, t_envlist *envlist, t_varlist *varlist)
{
	char	*varname;
	char	*expanded_val;

	varname = ft_getvarname(str, index);
	if (!varname)
		ft_printf("%s", &str[index + 1]);
	else
	{
		expanded_val = ft_getenv(varname, envlist, varlist);
		if (expanded_val != NULL)
			ft_printf("%s", expanded_val);
	}
}

char	*ft_getenv(char *varname, t_envlist *envlist, t_varlist *varlist)
{
	while (varlist != NULL && varlist->varname != NULL)
	{
		if (ft_strncmp(varname, varlist->varname, ft_strlen(varname)) == 0)
			return (varlist->value);
		else if (varlist->next == NULL)
			return (NULL);
		else
			varlist = varlist->next;
	}
	while (envlist != NULL && envlist->varname != NULL)
	{
		if (ft_strncmp(varname, envlist->varname, ft_strlen(varname)) == 0)
			return (envlist->value);
		else if (envlist->next == NULL)
			return (NULL);
		else
			envlist = envlist->next;
	}
	return (NULL);
}
