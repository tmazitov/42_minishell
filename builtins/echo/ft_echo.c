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

/// @brief ft_echo handles the string with echo as command and multiple 
/// @brief arguments
/// @param str string in format "echo arg1 arg2 arg3 ..."
void	ft_echo(char *str, t_envlist *envlist, t_varlist *varlist)
{
	char	**cmd_split;
	int		len;

	len = 1;
	cmd_split = ft_splittoken(str);
	cmd_split = str_token(cmd_split);
	if ((cmd_split[len] != NULL) && ft_strncmp(cmd_split[len], "-n", 2) == 0)
		len++;
	while (cmd_split[len] != NULL)
	{
		ft_printparams(str, cmd_split[len], envlist, varlist);
		len++;
		if ((cmd_split[len] != NULL))
		{
			if ((size_t)(ft_strstr(str, cmd_split[len]) > \
				ft_strstr(str, cmd_split[len - 1])) + \
				ft_strlen(cmd_split[len - 1]))
				ft_printf(" ");
			str = ft_strstr(str, cmd_split[len]);
		}
	}
	if (!((cmd_split[1] != NULL) && ft_strncmp(cmd_split[1], "-n", 2) == 0))
		ft_printf("\n");
	free_pointer(cmd_split);
}

/// @brief print the arguments of echo
/// @param cmd_split double pointer from ft_split excluding cmd_split quotes
void	ft_printparams(char *str, char *cmd_split, t_envlist *envlist, \
	t_varlist *varlist)
{
	(void)str;
	if (cmd_split[0] == '\'')
		ft_printsquotes(cmd_split);
	else if (cmd_split[0] == '$')
		ft_printexpansion(cmd_split, 1, envlist, varlist);
	else if (cmd_split[0] == '\"')
		ft_printdquotes(cmd_split, envlist, varlist);
	else
		ft_printf("%s", cmd_split);
}

/// @brief expand the $var and get it's value. Otherwise print it as string
/// @param str string with $ sign
/// @param index next index of the index of $ sign
void	ft_printexpansion(char *str, int index, t_envlist *envlist, \
	t_varlist *varlist)
{
	char	*varname;
	char	*expanded_val;

	if (ft_strncmp("$", str, ft_strlen(str)) == 0)
	{
		ft_printf("$");
		return ;
	}
	else if (str[index] == '?')
	{
		ft_printf("%d", status_code(GET_HISTORY, -1));
		while (str[index + 1] != ' ' && str[index + 1] != '\0')
			write(1, &str[++index], 1);
		return ;
	}
	varname = ft_getvarname(str, index);
	if (!varname)
		ft_printf("%s", varname);
	else
	{
		expanded_val = ft_getenv(varname, envlist, varlist);
		if (expanded_val != NULL)
			ft_printf("%s", expanded_val);
		free(varname);
	}
}

char	*ft_getenv(char *varname, t_envlist *envlist, t_varlist *varlist)
{
	while (varlist != NULL && varlist->varname != NULL)
	{
		if ((ft_strncmp(varname, varlist->varname, \
			ft_strlen(varlist->varname)) == 0) && \
			(ft_strlen(varname) == ft_strlen(varlist->varname)))
			return (varlist->value);
		else
			varlist = varlist->next;
	}
	while (envlist != NULL && envlist->varname != NULL)
	{
		if ((ft_strncmp(varname, envlist->varname, \
			ft_strlen(envlist->varname)) == 0) && \
			(ft_strlen(varname) == ft_strlen(envlist->varname)))
			return (envlist->value);
		else
			envlist = envlist->next;
	}
	return (NULL);
}
