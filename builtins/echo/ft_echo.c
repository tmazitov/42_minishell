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
void	ft_echo(char *str)
{
	char	**cmd_split;

	cmd_split = ft_splittoken(str);
	if (!cmd_split)
		return ;
	cmd_split = str_token(cmd_split);
	ft_printparams(cmd_split);
	free_pointer(cmd_split);
}

/// @brief print the arguments of echo
/// @param cmd_split double pointer from ft_split from echo string excluding quotes
void	ft_printparams(char **cmd_split)
{
	int	len;

	len = 1;
	while (cmd_split[len] != NULL)
	{
		if (cmd_split[len][0] == '\'')
			ft_printsquotes(cmd_split[len]);
		else if (cmd_split[len][0] == '$')
			ft_printexpansion(cmd_split[len], 1);
		else if (cmd_split[len][0] == '\"')
			ft_printdquotes(cmd_split[len]);
		else
			ft_printf("%s", cmd_split[len]);
		len++;
		if (cmd_split[len] != NULL)
			ft_printf(" ");
	}
	ft_printf("\n");
}

/// @brief print arguments inside double quotes
/// @param str string with double quotes
void	ft_printdquotes(char *str)
{
	int	len;

	len = 0;
	str++;
	while (str[len] != '\"' && str[len] != '\0')
	{
		if (str[len] == '$')
		{
			ft_printexpansion(str, ++len);
			while (!ft_isspace(str[len]) && str[len] != '\0' && \
					str[len] != '\"')
				len++;
		}
		else
			write(1, &str[len++], 1);
	}
}

/// @brief print arguemnts inside single quotes, retaining its literal meaning
/// @param str string with single quotes
void	ft_printsquotes(char *str)
{
	int	len;

	len = 0;
	str++;
	while (str[len] != '\'' && str[len] != '\0')
	{
		write(1, &str[len], 1);
		len++;
	}
}

/// @brief expand the $var and get it's value. Otherwise print it as string
/// @param str string with $ sign
/// @param index next index of the index of $ sign
void	ft_printexpansion(char *str, int index)
{
	int		len;
	char	*varname;
	char	*expanded_val;

	varname = ft_getvarname(str, index);
	if (!varname)
		ft_printf("%s", &str[index + 1]);
	else
	{
		expanded_val = getenv(varname);
		if (expanded_val != NULL)
			ft_printf("%s", expanded_val);
	}
}
