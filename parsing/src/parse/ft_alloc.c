/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:18:20 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/09 17:02:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief reallocate memory of a double pointer, adding a pointer at the
/// end index of the double pointer.
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
	old_size = ft_strlen_dp(s);
	if (!input || !*input)
		return (s);
	len = old_size + 1;
	out = (char **)malloc(sizeof(char *) * (len + 1));
	if (!out)
		return (NULL);
	while (count < old_size)
	{
		out[count] = s[count];
		count++;
	}
	out[count] = ft_strdup(input);
	count++;
	out[count] = NULL;
	free(s);
	return (out);
}

char	**safe_dp_malloc(int len)
{
	char	**out;

	out = (char **)malloc(sizeof(char *) * len);
	if (out == NULL)
		return (NULL);
	if (len == 1)
		out[0] = NULL;
	return (out);
}

/// @brief create new pointer from input string specifying the
// start and end index
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
