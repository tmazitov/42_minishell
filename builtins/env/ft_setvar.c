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
	t_varlist *var_head;

	index = 0;
	var_head = *varlist;
	var = ft_splittoken_setvar(str);
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
	free_pointer(var);
	*varlist = var_head;
	return (1);
}

char	**ft_handlesetvarsplit(char *str, char **var)
{
	char	**out;
	int		count;
	int		index;

	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
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
	free_pointer(var);
	return (out);
}

int	ft_setvarname(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	*varname;
	char	*varvalue;

	ft_printf("address str: %p\n", &str);
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
	{
		ft_setvarlist(ft_strdup(varname), ft_strdup(varvalue), 1, varlist);
		if (ft_checkvarenv(varname, *envlist))
			ft_setenvlist(ft_strdup(varname), ft_strdup(varvalue), 1, envlist);
		free(varname);
		free(varvalue);
	}
	return (1);
}

int	ft_setenvlist(char *varname, char *varvalue, int overwrite, \
	t_envlist **envlist)
{
	if ((*envlist)->varname == NULL && (*envlist)->value == NULL)
	{
		(*envlist)->varname = varname;
		(*envlist)->value = varvalue;
		(*envlist)->next = NULL;
		return (1);
	}
	while ((*envlist) != NULL && overwrite > 0)
	{
		if (ft_compname(varname, (*envlist)->varname))
		{
			free((*envlist)->value);
			(*envlist)->value = varvalue;
			free(varname);
			return (2);
		}
		else if ((*envlist)->next == NULL)
		{
			(*envlist)->next = ft_create_env(NULL, varname, varvalue);
			free(varname);
			return (1);
		}
		else
			(*envlist) = (*envlist)->next;
	}
	free(varname);
	return (3);
}

int	ft_setvarlist(char *varname, char *varvalue, int overwrite, \
	t_varlist **varlist)
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
		if (ft_compname(varname, (*varlist)->varname))
		{
			free((*varlist)->value);
			(*varlist)->value = varvalue;
			free(varname);
			return (2);
		}
		else if ((*varlist)->next == NULL)
		{
			(*varlist)->next = ft_create_var(varname, varvalue);
			free(varname);
			return (1);
		}
		else
			(*varlist) = (*varlist)->next;
	}
	free(varname);
	return (3);
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
		ft_printf("address start: %p\n", &start);
		ft_printf("address end: %p\n", &end);
		var = ft_splitvarvalue(start, envlist, varlist);
	}
	else
	{
		len = (end - start + 1);
		var = malloc(sizeof(char) * (len));
		if (var == NULL)
			return (NULL);
		ft_bzero(var, len);
		while (start < end && count < len - 1)
		{
			var[count] = start[count];
			count++;
		}
		var[count] = '\0';
	}
	ft_printf("var %s\n", var);
	return (var);
}

char	*ft_splitvarvalue(char *start, t_envlist **envlist, t_varlist **varlist)
{
	char	**cmd_split;
	int		len;
	char	*out;
	char	*str_temp;

	len = 0;
	out = malloc(sizeof(char) * 1);
	out[0] = '\0';
	cmd_split = ft_splittoken_setvar(start);
	if (!cmd_split)
		return (NULL);
	cmd_split = str_token(cmd_split);
	while (cmd_split[len] != NULL)
	{
		ft_printf("str: %s\n", cmd_split[len]);
		if (cmd_split[len][0] == '\'')
		{
			str_temp = ft_getvaluesquotes(cmd_split[len]);
			out = ft_mergevarval(start, out, str_temp);
			free(str_temp);
		}
		else if (cmd_split[len][0] == '\"' || cmd_split[len][0] == '$')
		{
			str_temp = ft_getvaluedquotes(cmd_split[len], envlist, varlist);
			out = ft_mergevarval(start, out, str_temp);
			free(str_temp);
		}
		else
			out = ft_mergevarval(start, out, ft_strdup(cmd_split[len]));
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
