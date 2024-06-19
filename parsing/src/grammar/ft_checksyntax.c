/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksyntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:52:38 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 21:12:53 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

bool	ft_checksyntax(t_tokens *tokens)
{
	if (!tokens)
		return (false);
	if (!ft_checkstart(tokens))
		return (false);
	return (true);
}

int	ft_checkquotes_grammar(char *str)
{
	int		index;
	char	c;

	index = -1;
	c = '0';
	while (str[++index])
	{
		if (str[index] == '\"' && c == '0')
			c = '\"';
		else if (str[index] == '\'' && c == '0')
			c = '\'';
		else if (str[index] && str[index] == '\'' && c == '\'')
			c = '0';
		else if (str[index] && str[index] == '\"' && c == '\"')
			c = '0';
	}
	if (c != '0')
		return (ft_err_p("bash: syntex error, uneven number of ", &c, \
			" quotes\n"), 0);
	else
		return (1);
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
		ft_err_p("bash: syntax error, uneven number of single quotes\n", \
			NULL, NULL);
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
		ft_err_p("bash: syntax error, uneven number of double quotes\n", \
			NULL, NULL);
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
		ft_err_p("bash: syntex error, uneven number of parenthesis\n", \
			NULL, NULL);
		return (false);
	}
	else
		return (true);
}
