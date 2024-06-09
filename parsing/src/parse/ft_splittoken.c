/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:04 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/09 05:20:32 by emaravil         ###   ########.fr       */
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
	spval->index = 0;
	if (ft_checksquotes(str) == 0)
		return (NULL);
	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
	spval->token_count = 0;
	while (str[spval->index] != '\0')
	{
		while (str[spval->index] && (ft_isspace(str[spval->index]) > 0))
			spval->index++;
		out = ft_checkstring(out, str, spval);
		out = ft_checkquotes(out, str, spval);
	}
	free(spval);
	return (out);
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
	return (true);
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
	char	**out_temp;
	char	*str_temp;
	int		start;

	start = *index;
	out = in;
	out_temp = NULL;
	while (handlestring_cond(str, *index))
		*index += 1;
	str_temp = ft_assignstring(str, start, *index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
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
	str_temp = NULL;
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
	}
	free(str);
	return (out);
}

char	**ft_checkadjacent(char **in, char *str, int *start, int *index)
{
	char	**out;

	out = in;
	if (*index > *start)
	{
		out = ft_realloc_dp(out, \
			ft_assignstring(str, *start, *index), *index - *start);
		(*start) = (*index);
	}
	if (ft_isdigit(str[*index + 1]) != 0)
	{
		out = ft_realloc_dp(out, \
			ft_assignstring(str, *index, *index + 2), 2);
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
	// while (str[*index] != '\0' && str[*index] != c)
	while ((str[*index] != '\0'))
		*index += 1;
	// if (str[*index] == c)
	// 	*index += 1;
	// else
	// {
	// 	ft_printf("bash: syntex error, uneven number of %c quotes\n", c);
	// 	free_pointer(out);
	// 	return (NULL);
	// }
	str_temp = ft_assignstring(str, start, *index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
	return (out);
}
