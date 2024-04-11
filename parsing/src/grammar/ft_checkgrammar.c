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

#include "../../includes/parse.h"

bool	ft_shellgrammar(t_tokens *tokens)
{
	if (!tokens)
		return (false);
	if (!ft_completecommand(tokens))
		return (false);
	return (true);
}

bool	ft_completecommand(t_tokens *tokens)
{
	t_tokens	*token_start;
	t_tokens	*token_end;

	token_start = tokens;
	while (tokens != NULL)
	{
		token_end = tokens->next;
		if (tokens->next != NULL && tokens->next->type == PIPE)
			if (!ft_ioredir(token_start, token_end))
				return (false);
		if (tokens->type == PIPE)
		{
			token_end = tokens;
			token_start = token_end;
			if (tokens->next != NULL)
				token_start = tokens->next;
			if (!ft_checkpipe(tokens))
				return (false);
		}
		tokens = tokens->next;
	}
	if (!ft_ioredir(token_start, token_end))
		return (false);
	return (true);
}

bool	ft_checkpipe(t_tokens *tokens)
{
	if (tokens->next == NULL || tokens->next->type == PIPE)
	{
		ft_printf("bash: syntex error near unexpected token '%s'\n", \
			tokens->value);
		return (false);
	}
	return (true);
}

bool	ft_ioredir(t_tokens *token_start, t_tokens *token_end)
{
	t_tokens	*tokens;

	tokens = token_start;
	while (tokens != NULL && tokens != token_end)
	{
		if (tokens->type == REDIR)
		{
			if (tokens->next == NULL)
			{
				ft_printf("bash: syntex error near unexpected ");
				ft_printf("token 'newline'\n");
				return (false);
			}
			else if (tokens->next->type != WORD)
			{
				ft_printf("bash: syntex error near unexpected token '%s'\n", \
					tokens->next->value);
				return (false);
			}
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	ft_checkstart(t_tokens *tokens)
{
	if ((tokens)->type != WORD && tokens->type != REDIR)
	{
		ft_printf("bash: syntex error near unexpected token '%s'\n", \
			tokens->value);
		return (false);
	}
	else
		return (true);
}
