/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_utils_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:53:32 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/18 19:19:16 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

char	*ft_mergevarval(char *str, char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	(void)str;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = ft_copyvarvalues(s1, s2, len1, len2);
	free(s1);
	return (out);
}

char	*ft_copyvarvalues(char *s1, char *s2, size_t len1, size_t len2)
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

char	*ft_getvaluedquotes(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	*out;
	int		len;
	int		offset;
	int		count;

	(void)envlist;
	(void)varlist;
	len = ft_strlen(str);
	if (str[0] == '\"')
		len--;
	out = malloc(sizeof(char) * (len + 1));
	ft_bzero(out, (len + 1));
	count = 0;
	offset = 0;
	while (str[count + offset] != '\0')
	{
		if (str[count + offset] == '\"')
			offset++;
		else
		{
			out[count] = str[count + offset];
			count++;
		}
	}
	return (out);
}

char	*ft_expanddquotes(char *str, int len, t_envlist **envlist, \
	t_varlist **varlist)
{
	char	**cmd;
	char	*str_temp;
	char	*out;

	out = malloc(sizeof(char) * 1);
	out[0] = '\0';
	str_temp = str;
	cmd = ft_splittoken(str);
	cmd = str_token(cmd);
	while (cmd[len] != NULL)
	{
		if ((len > 0) && ft_checkexportsplit(str_temp, cmd[len - 1], cmd[len]))
			out = ft_mergevarval(str_temp, out, " ");
		str_temp = ft_strstr(str_temp, cmd[len]);
		if (cmd[len][0] != '$')
			out = ft_mergevarval(str_temp, out, cmd[len++]);
		else
			if (ft_getenv((cmd[len] + 1), *envlist, *varlist))
				out = ft_mergevarval(str_temp, out, ft_getenv((cmd[len++] + 1), \
				*envlist, *varlist));
	}
	free(str);
	return (free_pointer(cmd), out);
}

char	*ft_getvaluesquotes(char *str)
{
	char	*out;
	int		len;
	int		offset;
	int		count;

	len = ft_strlen(str);
	len--;
	out = malloc(sizeof(char) * len);
	ft_bzero(out, len);
	count = 0;
	offset = 0;
	while (str[count + offset] != '\0')
	{
		if (str[count + offset] == '\'')
			offset++;
		else
		{
			out[count] = str[count + offset];
			count++;
		}
	}
	return (out);
}
