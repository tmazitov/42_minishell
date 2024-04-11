/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksyntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:52:38 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 02:00:13 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_checksyntax(t_tokens *tokens)
{
	if (!tokens)
		return (false);
	if (!ft_checkstart(tokens))
		return (false);
	if (!ft_checkparam(tokens))
		return (false);
	if (!ft_checkparenthesis(tokens))
		return (false);
	return (true);
}

int	ft_checksquotes(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			count++;
		index++;
	}
	if (count % 2 != 0)
	{
		ft_printf("bash: syntex error, uneven number of single quotes\n");
		return (0);
	}
	else
		return (ft_checkdquotes(str));
}

int	ft_checkdquotes(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == '\"')
			count++;
		index++;
	}
	if (count % 2 != 0)
	{
		ft_printf("bash: syntex error, uneven number of double quotes\n");
		return (0);
	}
	else
		return (1);
}

bool	ft_checkparenthesis(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL)
	{
		if (tokens->value[0] == '(')
			count++;
		if (tokens->value[0] == ')')
			count--;
		tokens = tokens->next;
	}
	if (count != 0)
	{
		ft_printf("bash: syntex error, uneven number of parenthesis\n");
		return (false);
	}
	else
		return (true);
}

int	ft_checkcbrackets(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == '{')
			count++;
		if (str[index] == '}')
			count--;
		index++;
	}
	if (count != 0)
	{
		ft_printf("bash: syntex error, uneven number of brackets\n");
		return (0);
	}
	else
		return (1);
}
