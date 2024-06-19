/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:12:36 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 02:06:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief checks for the operators, adds spaces to before and after
/// every operator
/// @brief at every token (quoted tokens are not included)
/// @param str_input the old double pointer containing the tokens
/// @return
char	**str_token(char **str_input)
{
	char			**out;
	int				count;
	char			*str_operator;

	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
	out[0] = NULL;
	count = 0;
	while (str_input[count] != NULL)
	{
		if (str_input[count][0] != '\"' && str_input[count][0] != '\'')
		{
			str_operator = ft_checkoperator(str_input[count]);
			out = ft_handletokens(out, str_operator);
		}
		else
		{
			out = ft_realloc_dp(out, str_input[count], ft_strlen_dp(out) + 1);
			free(str_input[count]);
		}
		count++;
	}
	free(str_input);
	return (out);
}

/// @brief splits the tokens to operators and reallocates new double pointer
/// memory 
/// @brief separating the token words to operators.
/// @param outdp the reallocated double pointer
/// @param str input string with spaces added to before and after the operator
/// @return the new double pointer
char	**ft_handletokens(char **outdp, char *str)
{
	char	**str_split;
	int		token_count;
	int		count;

	str_split = ft_splittoken(str);
	token_count = ft_strlen_dp(str_split);
	count = 0;
	while (count < token_count)
	{
		outdp = ft_realloc_dp(outdp, str_split[count], ft_strlen_dp(outdp) + 1);
		free(str_split[count]);
		count++;
	}
	free(str_split);
	free(str);
	return (outdp);
}

/// @brief creates a t_tokens struct with token_type, value, and next 
/// t_token pointer
/// @param str_token double pointer array of tokens
/// @return t_tokens head
t_tokens	*tokenize_input(char **str_token)
{
	t_tokens	*head;
	t_tokens	*tail;
	t_tokens	*token;

	head = NULL;
	tail = NULL;
	token = NULL;
	while (*str_token != NULL)
	{
		token = (t_tokens *)malloc(sizeof(t_tokens));
		if (!token)
			return (NULL);
		token->type = WORD;
		if (ft_strncmp(*str_token, "|", 1) == 0)
			token->type = PIPE;
		else if (((ft_strchr(*str_token, '>') != 0) || \
			(ft_strchr(*str_token, '<') != 0)) && ((*str_token[0] != '\"') && \
			(*str_token[0] != '\'')))
			token->type = REDIR;
		token->value = ft_token_value(*str_token);
		head = ft_sethead_token(head, tail, token);
		str_token++;
	}
	return (head);
}

/// @brief assigns pointer value to t_tokens struct
/// @param str_token token value
/// @return
char	*ft_token_value(char *str_token)
{
	char	*token_val;

	token_val = malloc(sizeof(char) * (ft_strlen(str_token)) + 1);
	if (token_val == NULL)
		return (NULL);
	ft_strlcpy(token_val, str_token, ft_strlen(str_token) + 1);
	return (token_val);
}

/// @brief adds the current token to the next token traversing from
/// the head pointer
/// @param head starting pointer of the token list
/// @param tail end pointer of the token list
/// @param token current token
/// @return starting pointer
t_tokens	*ft_sethead_token(t_tokens *head, t_tokens *tail, t_tokens *token)
{
	t_tokens	*s;

	s = head;
	(void)tail;
	token->next = NULL;
	if (!head)
	{
		head = token;
		return (head);
	}
	while (s != NULL)
	{
		if (s->next == NULL)
			break ;
		s = s->next;
	}
	s->next = token;
	return (head);
}
