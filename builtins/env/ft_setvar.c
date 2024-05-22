/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkgrammar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:34:08 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/11 18:35:51 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_setvar(char *str, t_envlist **envlist, t_varlist **varlist)
{
	int		out;
	char	**var;
	int		index;

	index = 0;
	var = ft_splittoken(str);
	var = str_token(var);
	var = ft_handlesetvarsplit(str, var);
	if (!var)
		return (0);
	while (var[index] != NULL)
	{
		out = ft_setvarname(var[index], envlist, varlist);
		if (out == 0)
			return (ft_printf("%s: command not found\n", var[index]), 0);
		index++;
	}
	return (1);
}

char	**ft_handlesetvarsplit(char *str, char **var)
{
	char	**out;
	int		count;
	int		index;

	out = (char **)malloc(sizeof(char *) * 1);
	out[0] = NULL;
	count = 0;
	index = -1;
	while (var[count] != NULL)
	{
		if ((count > 0) && ((size_t)(ft_strstr(str, var[count]) - \
			ft_strstr(str, var[count - 1])) == ft_strlen(var[count - 1])))
		{
			out[index] = ft_mergevarval(str, out[index], var[count]);
			str = ft_strstr(str, var[count++]);
		}
		else if ((count > 0) && (size_t)(ft_strstr(str, var[count]) - \
			ft_strstr(str, var[count - 1])) > ft_strlen(var[count - 1]) && \
			(!ft_strchr(var[count], '=')))
			return (ft_printf("%s: command not found\n", var[count]), NULL);
		else
		{
			index++;
			out = ft_realloc_dp(out, var[count++], ft_strlen_dp(out) + 1);
		}
	}
	free(var);
	return (out);
}

int	ft_setvarname(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char		*varname;
	char		*varvalue;

	varname = ft_splitequalsign(str, ft_strchr(str, '='), envlist, varlist);
	varvalue = ft_splitequalsign(ft_strchr(str, '='), \
		ft_strchr(str, '\0'), envlist, varlist);
	if (!varname || !ft_checkvarname(varname))
	{
		if (varname)
			free(varname);
		if (varvalue)
			free(varvalue);
		return (0);
	}
	else
		if (ft_checkvarenv(varname, *envlist))
			ft_setenvlist(varname, varvalue, 1, envlist);
		else
			ft_setvarlist(varname, varvalue, 1, varlist);
	return (1);
}

int	ft_setenvlist(char *varname, char *varvalue, int overwrite, t_envlist **envlist)
{
	if ((*envlist)->varname == NULL && (*envlist)->value == NULL)
	{
		(*envlist)->varname = varname;
		(*envlist)->value = varvalue;
		(*envlist)->next = NULL;
		return (2);
	}
	while ((*envlist) != NULL && overwrite > 0)
	{
		if (ft_strncmp(varname, (*envlist)->varname, ft_strlen(varname)) == 0)
		{
			(*envlist)->value = varvalue;
			return (2);
		}
		else if ((*envlist)->next == NULL)
		{
			(*envlist)->next = ft_create_env(NULL, varname, varvalue);
			return (2);
		}
		else
			(*envlist) = (*envlist)->next;
	}
	return (1);
}

int	ft_setvarlist(char *varname, char *varvalue, int overwrite, t_varlist **varlist)
{
	if ((*varlist)->varname == NULL && (*varlist)->value == NULL)
	{
		(*varlist)->varname = varname;
		(*varlist)->value = varvalue;
		(*varlist)->next = NULL;
		return (1);
	}
	while ((*varlist) != NULL && overwrite > 0)
	{
		if (ft_strncmp(varname, (*varlist)->varname, ft_strlen(varname)) == 0)
		{
			(*varlist)->value = varvalue;
			return (2);
		}
		else if ((*varlist)->next == NULL)
		{
			(*varlist)->next = ft_create_var(varname, varvalue);
			return (2);
		}
		else
			(*varlist) = (*varlist)->next;
	}
	return (1);
}

char	*ft_splitequalsign(char *start, char *end, t_envlist **envlist, \
	t_varlist **varlist)
{
	char	*var;
	size_t	len;
	size_t	count;

	count = 0;
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
		ft_bzero(var, len);
		while (start < end && count < len - 1)
		{
			var[count] = start[count];
			count++;
		}
		var[count] = '\0';
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
	cmd_split = ft_splittoken(start);
	if (!cmd_split)
		return (NULL);
	cmd_split = str_token(cmd_split);
	while (cmd_split[len] != NULL)
	{
		if (cmd_split[len][0] == '\'')
			out = ft_mergevarval(start, out, \
				ft_getvaluesquotes(cmd_split[len]));
		else if (cmd_split[len][0] == '\"' || cmd_split[len][0] == '$')
			out = ft_mergevarval(start, out, \
				ft_getvaluedquotes(cmd_split[len], envlist, varlist));
		else
			out = ft_mergevarval(start, out, cmd_split[len]);
		len++;
	}
	free_pointer(cmd_split);
	return (out);
}

char	*ft_mergevarval(char *str, char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	(void)str;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = ft_copyvarvalues(s1, s2, len1, len2);
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
	if (s1 && *s1)
		free(s1);
	out[index] = '\0';
	return (out);
}



char	*ft_getvaluedquotes(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	*out;
	int		len;
	int		offset;
	int		count;

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
	out = ft_expanddquotes(out, 0, envlist, varlist);
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
		if ((len > 0) && ((size_t)(ft_strstr(str_temp, cmd[len]) - \
			ft_strstr(str_temp, cmd[len - 1])) > ft_strlen(cmd[len - 1])))
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
