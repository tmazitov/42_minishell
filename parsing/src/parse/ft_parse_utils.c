/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:27:59 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 18:41:54 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	ft_strlen_dp(char **s)
{
	int	count;

	count = 0;
	while (s[count])
	{
		count++;
	}
	return (count);
}

void	free_pointer(char **s)
{
	int	count;
	int	len;

	len = ft_strlen_dp(s);
	count = 0;
	while (count < len)
	{
		free(s[count]);
		count++;
	}
}

void	print_tokens(t_tokens *head)
{
	t_tokens	*token;

	token = head;
	ft_printf("o---------------------o---------------------o\n");
	ft_printf("|        VALUE        |         TYPE        |\n");
	ft_printf("o---------------------o---------------------o\n");
	while (token != NULL)
	{
		ft_printf("| %19s | %19s |\n", token->value, enum_word(token->type));
		token = token->next;
	}
	ft_printf("o---------------------o---------------------o\n");
}

char	*enum_word(t_tokentype tokentype)
{
	if (tokentype == WORD)
		return ("WORD");
	else if (tokentype == REDIR)
		return ("REDIR");
	else if (tokentype == PIPE)
		return ("PIPE");
	else if (tokentype == SEMICOLON)
		return ("SEMICOLON");
	else if (tokentype == END)
		return ("END");
	else
		return ("");
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
