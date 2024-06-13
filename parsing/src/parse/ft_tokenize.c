/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:14:38 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/13 14:34:54 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

/// @brief checks operator character (<,>,|,(,),) from the input string and 
/// @brief add a space to before and after of the character.
/// @brief counts the new length including the total spaces added.
/// @example echo string>>output.txt becomes echo string >> output.txt
/// @param c input string
/// @return new string as shown in the example.
char	*ft_checkoperator(char *c)
{
	int		index;
	size_t	len;
	char	*out;
	int		mode;

	len = ft_strlen(c);
	index = -1;
	mode = 1;
	while (c[++index] != '\0')
	{
		mode = ft_modeoperator(c[index], mode);
		if (((c[index] == '<') || (c[index] == '>')) && mode == 1)
		{
			index += ft_checknextchar(c, index);
			len += 2;
		}
		else if ((c[index] == '|') && mode == 1)
			len += 2;
	}
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	out = ft_tokenize(out, c, len);
	free(c);
	return (out);
}

/// @brief checks operator character (<,>,|,(,),) from the input string, 
/// @brief add a space to before and after of the character and then copy the 
/// @brief rest of the characters in the string.
/// @param out the new allocated memory for the new pointer/string.
/// @param c old pointer/string
/// @param len length of the new pointer/string.
/// @enum i -> 
/// @enum o -> offset to the old string from the new string based on the added
/// spaces.
/// @return new pointer/string
char	*ft_tokenize(char *out, char *c, int len)
{
	int	i;
	int	o;
	int	mode;

	i = -1;
	o = 0;
	mode = 1;
	while (++i < len)
	{
		mode = ft_modeoperator(c[i - o], mode);
		if (((c[i - o] == '<') || (c[i - o] == '>') || ((ft_isdigit(c[i - o]) \
			> 0) && (ft_checkpid(c, i, o)))) && mode == 1)
			i = ft_handleredir(out, c, i, &o);
		else if (((c[i - o] == '|')) && mode == 1)
			i = ft_handleoper(out, c, i, &o);
		else
			out[i] = c[i - o];
	}
	out[i] = '\0';
	return (out);
}

/// @brief check pid before the redir operator and add it to the new token
/// before adding
/// @brief a space to before and after of the operator. pid should be a number
/// @param c input string
/// @param index index from input string
/// @param offset offset to the old string from the new string based on
/// the added spaces.
/// @return true if pid exist before redir, false if not
bool	ft_checkpid(char *c, int index, int offset)
{
	if ((index - offset) > 0)
	{
		if (ft_isspace(c[index - offset - 1]) > 0)
		{
			while (ft_isdigit(c[index - offset]) != 0)
			{
				if ((c[index + 1 - offset] == '>') || \
					(c[index + 1 - offset] == '<'))
					return (true);
				index++;
			}
		}
	}
	else
	{
		while (ft_isdigit(c[index - offset]) != 0)
		{
			if ((c[index + 1 - offset] == '>') || \
				(c[index + 1 - offset] == '<'))
				return (true);
			index++;
		}
	}
	return (false);
}

/// @brief adds space to before and after of the operator
/// @param out the new pointer/string with spaces added to before and
/// after the operator
/// @param c the old pointer/string
/// @param index index of the operator from the old pointer/string
/// @param offset offset to the old string from the new string based
/// on the added spaces
/// @return end index of the new pointer/string
int	ft_handleoper(char *out, char *c, int index, int *offset)
{
	out[index] = ' ';
	(*offset)++;
	index++;
	out[index] = c[index - *offset];
	(*offset)++;
	index++;
	out[index] = ' ';
	return (index);
}

/// @brief handle redir operator and check the next character if also a
/// redir operator
/// @param out the new pointer/string where spaces are added to before and
/// after of the redir operator.
/// @param c the old pointer/string
/// @param index where the redir starts (including the pid)
/// @param offset offset to the old string from the new string based on
/// the added spaces
/// @return end index of the new pointer/string
int	ft_handleredir(char *out, char *c, int index, int *offset)
{
	int	redir_type;

	out[index] = ' ';
	(*offset)++;
	while (ft_isdigit(c[++index - *offset]) != 0)
		out[index] = c[index - *offset];
	out[index] = c[index - *offset];
	redir_type = ft_checknextchar(c, index - *offset);
	if (redir_type == 1)
	{
		index++;
		out[index] = c[index - *offset];
	}
	if (redir_type == 2)
	{
		index++;
		out[index] = c[index - *offset];
	}
	(*offset)++;
	index++;
	out[index] = ' ';
	return (index);
}
