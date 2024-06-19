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
	char	**c;
	int		len;

	len = 1;
	c = ft_splittoken_setvar(str);
	c = str_token(c);
	while ((c[len] != NULL) && ft_compname("-n", c[len]))
		len++;
	while (c[len] != NULL)
	{
		ft_printparams(str, c[len], envlist, varlist);
		str = ft_strstr(str, c[len]);
		len++;
		if ((c[len] != NULL))
		{
			if ((size_t)(ft_strstr(str + ft_strlen(c[len - 1]), c[len]) > \
				(ft_strstr(str, c[len - 1])) + ft_strlen(c[len - 1])))
				ft_printf(" ");
			str = ft_strstr(str + ft_strlen(c[len - 1]), c[len]);
		}
	}
	if (!((c[1] != NULL) && ft_compname("-n", c[1])))
		ft_printf("\n");
	free_pointer(c);
}

/// @brief print the arguments of echo
/// @param cmd_split double pointer from ft_split excluding cmd_split quotes
void	ft_printparams(char *str, char *cmd_split, t_envlist *envlist, \
	t_varlist *varlist)
{
	(void)str;
	if (cmd_split[0] == '\'')
		ft_printsquotes(cmd_split);
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

	if (ft_compname("$", str))
	{
		ft_printf("$");
		return ;
	}
	else if (ft_compname("$?", str))
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

// void	ft_echo(char *str, t_envlist *envlist, t_varlist *varlist)
// {
// 	char	**c;
// 	int		len;
// 	int		count;
// 	int		index;
// 	char	*str_temp;

// 	count = 1;
// 	len = 0;
// 	str_temp = str;
// 	c = ft_splittoken_setvar(str);
// 	c = str_token(c);
// 	while ((c[len + count] != NULL) && ft_compname("-n", c[len + count]))
// 		count++;
// 	index = 0;
// 	while (index < count)
// 	{
// 		len = 0;
// 		str = str_temp;
// 		while (c[len + count] != NULL)
// 		{
// 			ft_printparams(str, c[len + count], envlist, varlist);
// 			str = ft_strstr(str, c[len + count]);
// 			len++;
// 			if ((c[len + count] != NULL))
// 			{
// 				if ((size_t)(ft_strstr(str + ft_strlen(c[len + count - 
// 1]), c[len + count]) > 
// 					(ft_strstr(str, c[len + count - 1])) + ft_strlen
// (c[len + count - 1])))
// 					ft_printf(" ");
// 				str = ft_strstr(str + ft_strlen(c[len + count - 1]), 
// c[len + count]);
// 			}
// 		}
// 		index++;
// 		if (index == count - 1)
// 			break ;
// 	}
// 	if (!((c[1] != NULL) && ft_compname("-n", c[1])))
// 		ft_printf("\n");
// 	free_pointer(c);
// }