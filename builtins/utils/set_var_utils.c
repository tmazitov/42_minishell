/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:04 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/21 01:52:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

/// @brief split input string into tokens. This function does not split spaces
/// in between single and double quotes
/// @brief functions included: ft_handlestring, ft_handlequotes,
/// ft_assignstring, ft_realloc_dp
/// @param str input pointer string
/// @return double pointer of tokens.
char	**ft_splittoken_setvar(char *str)
{
	t_splitvalues	spval;
	char			**out;

	spval.index = 0;
	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
	spval.token_count = 0;
	while (str[spval.index] != '\0')
	{
		while (str[spval.index] && (ft_isspace(str[spval.index]) > 0))
			spval.index++;
		if (str[spval.index] && !(ft_isspace(str[spval.index])) && \
			str[spval.index] != '\'' && str[spval.index] != '\"' && \
			!(str[spval.index] == '$' && str[spval.index + 1] == '\"') && \
			!(str[spval.index] == '$' && str[spval.index + 1] == '\''))
			out = ft_handlestring_setvar(out, str, &spval.index, \
			(++spval.token_count));
		if (str[spval.index] == '\'' || str[spval.index] == '\"' || \
			(str[spval.index] == '$' && str[spval.index + 1] == '\"') || \
			(str[spval.index] == '$' && str[spval.index + 1] == '\''))
			out = ft_handlequotes(out, str, &spval.index, \
			(spval.token_count + 2));
	}
	return (out);
}

bool	handlestring_cond_setvar(char *str, int index)
{
	if (str[index] != '\0' && !(ft_isspace(str[index])) && \
		str[index] != '\'' && str[index] != '\"' && !(str[index] == '$' && \
		str[(index) + 1] == '\"') && !(str[index] == '$' && \
		str[(index) + 1] == '\''))
		return (true);
	return (false);
}

/// @brief handles unqouted strings excluding spaces then reallocates memory
/// of the double pointer
/// @param in the old double pointer
/// @param str string input from readline/function
/// @param index index in str where a string starts. The string starts
/// right after a space.
/// @param token_count the new size of the new double pointer
/// @return new double pointer
char	**ft_handlestring_setvar(char **in, char *str, \
	int *index, int token_count)
{
	char	**out;
	char	**out_temp;
	char	*str_temp;
	int		start;

	start = *index;
	out = in;
	out_temp = NULL;
	while (handlestring_cond_setvar(str, *index))
		*index += 1;
	str_temp = ft_assignstring(str, start, *index);
	if (ft_strchr(str_temp, '$'))
	{
		out_temp = ft_splitstring(ft_strdup(str_temp));
		start = 0;
		while (out_temp[start] != NULL)
			out = ft_realloc_dp(out, out_temp[start++], token_count + 1);
		free_pointer(out_temp);
	}
	else
		out = ft_realloc_dp(out, str_temp, token_count + 1);
	free(str_temp);
	return (out);
}

void	ft_splitcond_b(char **out, char **var, char *str)
{
	ft_err_b(str, ": command not found\n", NULL);
	free_pointer(out);
	free_pointer(var);
}
