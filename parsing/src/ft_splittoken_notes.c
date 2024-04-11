/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:18:04 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/07 21:11:12 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	**ft_splittoken(char *str)
// {
// 	t_splitvalues sval;

// 	sval.index = 0;
// 	sval.out = (char **)malloc(sizeof(char *) * 1);
// 	sval.out[0] = NULL;
// 	sval.token_count = 0;
// 	while (str[sval.index] != '\0')
// 	{
// 		while (str[sval.index] && (ft_isspace(str[sval.index]) > 0))
// 			sval.index++;
// 		if (str[sval.index] && (ft_isspace(str[sval.index]) == 0) && str[sval.index] != '\'' \
// 			&& str[sval.index] != '\"')
// 		{
// 			sval.token_count++;
// 			sval.out = ft_handlestring(sval.out, str, sval.index, sval.token_count);
// 			sval.index = get_indexstring(str, sval.index);
// 		}
// 		if (str[sval.index] == '\'' || str[sval.index] == '\"')
// 		{
// 			sval.out = ft_handlequotes(sval.out, str, sval.index, sval.token_count + 2);
// 			if (sval.out == NULL)
// 				return (NULL);
// 			sval.index = get_indexquotes(str, sval.index);
// 		}
// 	}
// 	return (sval.out);
// }

char	**ft_splittoken(char *str)
{
	char	**out;
	int		token_count;
	int		index;
	t_splitvalues spval;

	spval.index = 0;
	spval.out = (char **)malloc(sizeof(char *) * 1);
	spval.out[0] = NULL;
	spval.token_count = 0;
	while (str[spval.index] != '\0')
	{
		while (str[spval.index] && (ft_isspace(str[spval.index]) > 0))
			spval.index++;
		if (str[spval.index] && (ft_isspace(str[spval.index]) == 0) && str[spval.index] != '\'' \
			&& str[spval.index] != '\"')
		{
			out = ft_handlestring(&out, str, spval.index, token_count + 1);
			index = get_indexstring(str, index);
		}
		if (str[index] == '\'' || str[index] == '\"')
		{
			out = ft_handlequotes(out, str, index, token_count + 2);
			if (out == NULL)
				return (NULL);
			index = get_indexquotes(str, index);
		}
	}
	return (out);
}

// char	**ft_splittoken(char *str)
// {
// 	char	**out;
// 	int		token_count;
// 	int		index;

// 	index = 0;
// 	out = (char **)malloc(sizeof(char *) * 1);
// 	out[0] = NULL;
// 	token_count = 0;
// 	while (str[index] != '\0')
// 	{
// 		while (str[index] && (ft_isspace(str[index]) > 0))
// 			index++;
// 		if (str[index] && (ft_isspace(str[index]) == 0) && str[index] != '\'' \
// 			&& str[index] != '\"')
// 		{
// 			token_count++;
// 			out = ft_handlestring(out, str, index, token_count);
// 			index = get_indexstring(str, index);
// 		}
// 		if (str[index] == '\'' || str[index] == '\"')
// 		{
// 			out = ft_handlequotes(out, str, index, token_count + 2);
// 			if (out == NULL)
// 				return (NULL);
// 			index = get_indexquotes(str, index);
// 		}
// 	}
// 	return (out);
// }

int	get_indexstring(char *str, int index)
{
	while (str[index] != '\0' && !(ft_isspace(str[index])) \
		&& str[index] != '\'' && str[index] != '\"')
		index++;
	// if (str[index] == '\'' || str[index] == '\"')
	// 	index = get_indexquotes(str, index);
	return (index);
}

int	get_indexquotes(char *str, int index)
{
	char	c;

	c = str[index];
	index++;
	while (str[index] != c)
		index++;
	index++;
	return (index);
}

char	**ft_handlestring(char **in, char *str, int index, int token_count)
{
	char	**out;
	char	*str_temp;
	int		start;

	start = index;
	out = in;
	while (str[index] != '\0' && !(ft_isspace(str[index])) \
		&& str[index] != '\'' && str[index] != '\"')
		index++;
	// if (str[index] == '\'' || str[index] == '\"')
	// 	index = get_indexquotes(str, index);
	str_temp = ft_assignstring(str, start, index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
	return (out);
}

char	**ft_handlequotes(char **in, char *str, int index, int token_count)
{
	char	**out;
	char	*str_temp;
	char	c;
	int		start;

	c = str[index];
	start = index;
	index++;
	out = in;
	while (str[index] != '\0' && str[index] != c)
		index++;
	if (str[index] == c)
		index++;
	else
	{
		ft_printf("bash: syntex error, uneven number of %c quotes\n", c);
		ft_freesplit(out);
		return (NULL);
	}
	str_temp = ft_assignstring(str, start, index);
	out = ft_realloc_dp(out, str_temp, token_count + 1);
	return (out);
}

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

void	free_pointer(char *s)
{
	int	count;
	int	len;

	len = ft_strlen(s);
	count = 0;
	while (count < len)
	{
		// free(s[count]);
		count++;
	}
}
