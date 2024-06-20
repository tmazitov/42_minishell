/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:52:06 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/20 16:35:31 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	**ft_handlesplittoken(char *str, char **var)
{
	char	**out;
	int		count;
	int		index;

	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
	count = -1;
	index = -1;
	while (var[++count] != NULL)
	{
		if ((count > 0) && ft_checknextsplit(str, var[count - 1], var[count]) \
			&& (!ft_strchr(var[count], '|')))
		{
			out[index] = ft_mergesplittoken(str, out[index], var[count]);
			str = ft_strstr(str + ft_strlen(var[count - 1]), var[count]);
		}
		else
		{
			index++;
			out = ft_realloc_dp(out, var[count], ft_strlen_dp(out) + 1);
		}
	}
	return (free_pointer(var), out);
}

char	**ft_checkquotes(char **out, char *str, t_splitvalues *spval)
{
	if (str[spval->index] == '\'' || str[spval->index] == '\"' || \
		(str[spval->index] == '$' && str[spval->index + 1] == '\"') || \
		(str[spval->index] == '$' && str[spval->index + 1] == '\''))
		out = ft_handlequotes(out, str, &spval->index, \
		(spval->token_count + 2));
	return (out);
}

char	**ft_checkstring(char **out, char *str, t_splitvalues *spval)
{
	if (str[spval->index] && !(ft_isspace(str[spval->index])) && \
		str[spval->index] != '\'' && str[spval->index] != '\"' && \
		!(str[spval->index] == '$' && str[spval->index + 1] == '\"') && \
		!(str[spval->index] == '$' && str[spval->index + 1] == '\''))
		out = ft_handlestring(out, str, &spval->index, \
			(++spval->token_count));
	return (out);
}

bool	handlestring_cond(char *str, int index)
{
	if (!(str[index] != '\0'))
		return (false);
	if (!(!(ft_isspace(str[index]))))
		return (false);
	if (str[index] == '\'')
		return (false);
	if (str[index] == '\"')
		return (false);
	return (true);
}

bool	ft_checkparam(t_tokens *tokens)
{
	int	index;

	while ((tokens) != NULL)
	{
		index = -1;
		while ((tokens)->value[++index] != '\0' && (tokens)->value[0] != \
			'\"' && (tokens)->value[0] != '\'')
		{
			if ((tokens)->value[index] == '$')
			{
				if ((tokens)->value[index + 1] != '\0' && \
					((ft_isalpha((tokens)->value[index + 1]) == 0) && \
					((tokens)->value[index + 1]) != '_') && (ft_isdigit \
					((tokens)->value[index + 1])) == 0 && ((tokens)->value \
					[index + 1] != '?') && ((tokens)->value[index + 1] \
					!= '\'') && ((tokens)->value[index + 1] != '\"'))
					return (ft_err_p("bash: syntax error, wrong parameter \
						name\n", NULL, NULL), false);
			}
		}
		tokens = tokens->next;
	}
	return (true);
}
