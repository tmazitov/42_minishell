/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesplittoken.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:08 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/14 19:49:16 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	*ft_mergesplittoken(char *str, char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	(void)str;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = ft_copyvarsplittoken(s1, s2, len1, len2);
	free(s1);
	return (out);
}

char	*ft_copyvarsplittoken(char *s1, char *s2, size_t len1, size_t len2)
{
	char	*out;
	size_t	index;

	out = malloc(sizeof(char) * (len1 + len2 + 1));
	ft_bzero(out, len1 + len2 + 1);
	if (!out)
		return (NULL);
	index = 0;
	while (index < len1)
	{
		out[index] = s1[index];
		index++;
	}
	while (index < (len1 + len2))
	{
		out[index] = s2[index - len1];
		index++;
	}
	out[index] = '\0';
	return (out);
}

bool	ft_checknextsplit(char *str, char *prevvar, char *currvar)
{
	if (((size_t)(ft_strstr(str + ft_strlen(prevvar), \
		currvar) - ft_strstr(str, prevvar)) == ft_strlen(prevvar)))
		return (true);
	else if (ft_strstr(prevvar, currvar))
	{
		prevvar = ft_strstr(prevvar, currvar);
		while (*prevvar)
		{
			if (!(prevvar + 1))
				break ;
			prevvar++;
		}
		if ((prevvar) && ((size_t)((&prevvar) - (&currvar)) == 1))
			return (true);
		else
			return (false);
	}
	else
		return (false);
}
