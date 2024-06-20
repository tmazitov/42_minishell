/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:04 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/20 19:59:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief split input string into tokens. This function does not split spaces 
/// in between single and double quotes
/// @brief functions included: ft_handlestring, ft_handlequotes, 
/// ft_assignstring, ft_realloc_dp
/// @param str input pointer string
/// @return double pointer of tokens.
char	**ft_splittoken(char *str)
{
	t_splitvalues	*spval;
	char			**out;

	spval = malloc(sizeof(t_splitvalues));
	if (spval == NULL)
		return (NULL);
	spval->index = 0;
	if (ft_checkquotes_grammar(str) == 0)
		return (free(spval), NULL);
	out = safe_dp_malloc(1);
	if (out == NULL)
		return (free(spval), NULL);
	spval->token_count = 0;
	while (str[spval->index] != '\0')
	{
		while (str[spval->index] && (ft_isspace(str[spval->index]) > 0))
			spval->index++;
		out = ft_checkstring(out, str, spval);
		out = ft_checkquotes(out, str, spval);
	}
	free(spval);
	out = ft_handlesplittoken(str, out);
	return (out);
}

/// @brief handles unqouted strings excluding spaces then reallocates memory
/// of the double pointer
/// @param in the old double pointer
/// @param str string input from readline/function
/// @param index index in str where a string starts. The string starts
/// right after a space.
/// @param token_count the new size of the new double pointer
/// @return new double pointer
char	**ft_handlestring(char **in, char *str, int *index, int token_count)
{
	char	**out;
	char	*str_temp;
	int		start;

	start = *index;
	out = in;
	while (handlestring_cond(str, *index))
		*index += 1;
	str_temp = ft_assignstring(str, start, *index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
	free(str_temp);
	return (out);
}

/// @brief split string on $
/// @param str input string
/// @return double pointer
char	**ft_splitstring(char *str)
{
	char	**out;
	int		index;
	int		start;
	char	*str_temp;

	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
	index = 0;
	start = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '$')
			out = ft_checkadjacent(out, str, &start, &index);
		else
			index++;
	}
	if (index > start)
	{
		str_temp = ft_assignstring(str, start, index);
		out = ft_realloc_dp(out, str_temp, 1);
		free(str_temp);
	}
	free(str);
	return (out);
}

char	**ft_checkadjacent(char **in, char *str, int *start, int *index)
{
	char	**out;
	char	*str_temp;

	out = in;
	if (*index > *start)
	{
		str_temp = ft_assignstring(str, *start, *index);
		out = ft_realloc_dp(out, str_temp, *index - *start);
		free(str_temp);
		(*start) = (*index);
	}
	if (ft_isdigit(str[*index + 1]) != 0)
	{
		str_temp = ft_assignstring(str, *index, *index + 2);
		out = ft_realloc_dp(out, str_temp, 2);
		free(str_temp);
		(*index) += 2;
		(*start) = (*index);
	}
	else
		(*index)++;
	return (out);
}

/// @brief handles single and double quotes from the input string/pointer. 
/// checks if the number of quotes is even.
/// @param in the old double pointer
/// @param str string input from readline/function
/// @param index index in str where quote starts
/// @param token_count the new size of the new double pointer
/// @return new double pointer
char	**ft_handlequotes(char **in, char *str, int *index, int token_count)
{
	char	**out;
	char	*str_temp;
	char	c;
	int		start;

	if (str[*index] == '$')
		(*index)++;
	c = str[*index];
	start = *index;
	*index += 1;
	out = in;
	while ((str[*index] != '\0') && str[*index] != c)
		*index += 1;
	if (str[*index] == c)
		*index += 1;
	else
	{
		ft_err_p("bash: syntax error, uneven number of ", &c, " quotes\n");
		free_pointer(out);
		return (NULL);
	}
	str_temp = ft_assignstring(str, start, *index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
	free(str_temp);
	return (out);
}
