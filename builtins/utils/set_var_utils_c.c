/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_utils_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:55:00 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 21:24:10 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

char	**ft_handlesetvarsplit(char *str, char **var)
{
	char	**out;
	int		c;
	int		index;

	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
	c = 0;
	index = -1;
	while (var[c] != NULL)
	{
		if ((c > 0) && ft_splitcond(str, var[c], var[c - 1], c) == 1)
		{
			out[index] = ft_mergevarval(str, out[index], var[c]);
			str = ft_strstr(str, var[c++]);
		}
		else if ((c > 0) && ft_splitcond(str, var[c], var[c - 1], c) > 1)
			return (ft_splitcond_b(out, var, var[c]), NULL);
		else
		{
			index++;
			out = ft_realloc_dp(out, var[c++], ft_strlen_dp(out) + 1);
		}
	}
	return (free_pointer(var), out);
}

int	ft_splitcond(char *str, char *curr_var, char *prev_var, int count)
{
	if ((count > 0) && ((size_t)(ft_strstr(str, curr_var) - \
			ft_strstr(str, prev_var)) == ft_strlen(prev_var)))
		return (1);
	else if ((count > 0) && (size_t)(ft_strstr(str, curr_var) - \
		ft_strstr(str, prev_var)) > ft_strlen(prev_var) && \
		(!ft_strchr(curr_var, '=')))
		return (2);
	return (0);
}

char	*ft_splitequalsign(char *start, char *end, t_envlist **envlist, \
	t_varlist **varlist)
{
	char	*var;
	size_t	len;
	size_t	count;

	count = -1;
	if (!start || !end)
		return (NULL);
	if (*start == '=' && start < end)
	{
		start++;
		var = ft_splitvarvalue(start, envlist, varlist);
	}
	else
	{
		len = (end - start + 1);
		var = malloc(sizeof(char) * (len));
		if (var == NULL)
			return (NULL);
		ft_bzero(var, len);
		while (start < end && ++count < len - 1)
			var[count] = start[count];
	}
	return (var);
}

char	*ft_splitvarvalue(char *start, t_envlist **envlist, t_varlist **varlist)
{
	char	**cmd_split;
	int		len;
	char	*out;

	len = 0;
	out = malloc(sizeof(char) * 1);
	out[0] = '\0';
	cmd_split = ft_splittoken_setvar(start);
	if (!cmd_split)
		return (NULL);
	cmd_split = str_token(cmd_split);
	while (cmd_split[len] != NULL)
	{
		out = ft_splitvarvalue_b(cmd_split[len], out, envlist, varlist);
		len++;
	}
	free_pointer(cmd_split);
	return (out);
}

char	*ft_splitvarvalue_b(char *str, char *out, t_envlist **envlist, \
	t_varlist **varlist)
{
	char	*str_temp;

	if (str[0] == '\'')
	{
		str_temp = ft_getvaluesquotes(str);
		out = ft_mergevarval(NULL, out, str_temp);
		free(str_temp);
	}
	else if (str[0] == '\"' || str[0] == '$')
	{
		str_temp = ft_getvaluedquotes(str, envlist, varlist);
		out = ft_mergevarval(NULL, out, str_temp);
		free(str_temp);
	}
	else
	{
		str_temp = ft_strdup(str);
		out = ft_mergevarval(NULL, out, str_temp);
		free(str_temp);
	}
	return (out);
}
