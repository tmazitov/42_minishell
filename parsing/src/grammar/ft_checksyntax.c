/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksyntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:52:38 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/09 07:47:00 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

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
		else if (str[index] && str[index] == '\'' && c != '0')
			c = '0';
		else if (str[index] && str[index] == '\"' && c != '0')
			c = '0';
	}
	if (c != '0')
		return (ft_printf("bash: syntex error, uneven number of %c quotes\n" \
			, c), 0);
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

bool	ft_checkparam(t_tokens *tokens)
{
	int	index;

	while ((tokens) != NULL)
	{
		index = 0;
		while ((tokens)->value[index] != '\0' && (tokens)->value[0] != \
			'\"' && (tokens)->value[0] != '\'')
		{
			if ((tokens)->value[index] == '$')
			{
				if ((tokens)->value[index + 1] != '\0' && \
					((ft_isalpha((tokens)->value[index + 1]) == 0) && \
					((tokens)->value[index + 1]) != '_') && \
					(ft_isdigit((tokens)->value[index + 1])) == 0 && \
					(tokens)->value[index + 1] != '?')
				{
					ft_printf("bash: syntax error, wrong parameter name\n");
					return (false);
				}
			}
			index++;
		}
		tokens = tokens->next;
	}
	return (true);
}
