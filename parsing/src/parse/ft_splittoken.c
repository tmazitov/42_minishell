/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:04 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/19 00:47:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief split input string into tokens. This function does not split spaces in between single and double quotes
/// @brief functions included: ft_handlestring, ft_handlequotes, ft_assignstring, ft_realloc_dp
/// @param str input pointer string
/// @return double pointer of tokens.
char	**ft_splittoken(char *str)
{
	t_splitvalues	spval;
	char			**out;

	spval.index = 0;
	out = (char **)malloc(sizeof(char *) * 1);
	out[0] = NULL;
	spval.token_count = 0;
	while (str[spval.index] != '\0')
	{
		while (str[spval.index] && (ft_isspace(str[spval.index]) > 0))
			spval.index++;
		if (str[spval.index] && !(ft_isspace(str[spval.index])) && \
			str[spval.index] != '\'' \
			&& str[spval.index] != '\"')
			out = ft_handlestring(out, str, &spval.index, \
			(++spval.token_count));
		if (str[spval.index] == '\'' || str[spval.index] == '\"')
		{
			out = ft_handlequotes(out, str, &spval.index, \
			(spval.token_count + 2));
			if (!out)
				return (NULL);
		}
	}
	return (out);
}

/// @brief handles unqouted strings excluding spaces then reallocates memory of the double pointer
/// @param in the old double pointer
/// @param str string input from readline/function
/// @param index index in str where a string starts. The string starts right after a space.
/// @param token_count the new size of the new double pointer
/// @return new double pointer
char	**ft_handlestring(char **in, char *str, int *index, int token_count)
{
	char	**out;
	char	*str_temp;
	int		start;

	start = *index;
	out = in;
	while (str[*index] != '\0' && !(ft_isspace(str[*index])) \
		&& str[*index] != '\'' && str[*index] != '\"')
		*index += 1;
	str_temp = ft_assignstring(str, start, *index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
	return (out);
}

/// @brief handles single and double quotes from the input string/pointer. checks if the number of quotes is even.
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

	c = str[*index];
	start = *index;
	*index += 1;
	out = in;
	while (str[*index] != '\0' && str[*index] != c)
		*index += 1;
	if (str[*index] == c)
		*index += 1;
	else
	{
		ft_printf("bash: syntex error, uneven number of %c quotes\n", c);
		free_pointer(out);
		return (NULL);
	}
	str_temp = ft_assignstring(str, start, *index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
	return (out);
}

/// @brief create new pointer from input string specifying the start and end index
/// @param str input string
/// @param start start index from input string
/// @param end end index from input string. end index is not included.
/// @return new string pointer
char	*ft_assignstring(char *str, int start, int end)
{
	int		count;
	char	*out;

	count = 0;
	out = malloc(sizeof(char) * (end - start + 1));
	if (!out)
		return (NULL);
	while (start < end)
	{
		out[count] = str[start];
		count++;
		start++;
	}
	out[count] = '\0';
	return (out);
}

/// @brief reallocate memory of a double pointer, adding a pointer at the end index of the double pointer.
/// @param s old double pointer
/// @param input pointer that is going to be added to the double pointer
/// @param len length of the new double pointer
/// @return return new double pointer
char	**ft_realloc_dp(char **s, char *input, int len)
{
	char	**out;
	int		old_size;
	int		count;

	count = 0;
	out = (char **)malloc(sizeof(char *) *(len + 1));
	old_size = ft_strlen_dp(s);
	while (count < old_size)
	{
		out[count] = s[count];
		count++;
	}
	out[count] = input;
	count++;
	out[count] = NULL;
	return (out);
}
