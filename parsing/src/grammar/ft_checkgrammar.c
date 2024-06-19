/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkgrammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:08 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 21:12:41 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief checks for complete command
/// @param tokens token list
/// @return true if complete command, false if not
bool	ft_shellgrammar(t_tokens *tokens)
{
	if (!tokens)
		return (false);
	if (!ft_completecommand(tokens))
		return (false);
	return (true);
}

/// @brief checks for the context free grammar of REDIR and PIPE
/// @param tokens token list
/// @return true if complete command, false if not
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

/// @brief check PIPE arguments if next is NULL or PIPE
/// @param tokens token PIPE
/// @return true if next is not NULL or not a PIPE
bool	ft_checkpipe(t_tokens *tokens)
{
	if (tokens->next == NULL || tokens->next->type == PIPE)
	{
		write(2, "bash: syntax error near unexpected token ", 41);
		write(2, tokens->value, ft_strlen(tokens->value));
		write(2, "\n", 1);
		return (false);
	}
	return (true);
}

/// @brief checks the arguments of REDIR, next should not be a NULL
/// it should be a WORD
/// @param token_start starting token where to check
/// @param token_end ending token where to check
/// @return true if the arguments of REDIR is not NULL and type WORD
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
				ft_err_p("bash: syntax error near unexpected a ", \
					"token 'newline'\n", NULL);
				return (false);
			}
			else if (tokens->next->type != WORD)
			{
				ft_err_p("bash: syntax error near unexpected token '", \
					tokens->next->value, "'\n");
				return (false);
			}
		}
		tokens = tokens->next;
	}
	return (true);
}

/// @brief check the starting word if a WORD or a REDIR
/// @param tokens token list
/// @return true if starting word is a WORD or a REDIR
bool	ft_checkstart(t_tokens *tokens)
{
	if ((tokens)->type != WORD && tokens->type != REDIR)
	{
		ft_err_p("bash: syntax error near unexpected token '", \
			tokens->value, "'\n");
		return (false);
	}
	else
		return (true);
}
