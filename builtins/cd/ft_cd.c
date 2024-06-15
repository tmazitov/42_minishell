/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:07:42 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/15 21:41:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_cd(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	currdir[PATH_MAX];
	char	*path;

	if (ft_strlen(str) > NAME_MAX)
		return (ft_printf("File name too long\n"), 0);
	getcwd(currdir, sizeof(currdir));
	path = ft_getpath(str, envlist, varlist);
	if (path == NULL)
		return (0);
	if (chdir(path) != 0)
	{
		ft_printf("bash: cd: %s: No such file or directory\n", path);
		return (free(path), 1);
	}
	ft_update_envlist(path, currdir, envlist);
	return (1);
}

char	*ft_getpath(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	**psplit;
	char	*path;

	psplit = ft_splittoken_setvar(str);
	psplit = str_token(psplit);
	psplit = ft_handlecdsplit(str, psplit);
	psplit[1] = ft_cdcleanvalue(psplit[1]);
	if (psplit[1] == NULL || (*psplit[1] == '~' && ft_strlen(psplit[1]) == 1))
		path = ft_copystring(ft_getenv("HOME", *envlist, *varlist));
	else if (*psplit[1] == '~' && ft_strlen(psplit[1]) > 1)
		path = ft_expandhomepath(psplit, *envlist, *varlist);
	else if (*psplit[1] == '-' && ft_strlen(psplit[1]) == 1)
	{
		path = ft_copystring(ft_getenv("OLDPWD", *envlist, *varlist));
		if (path == NULL)
			return (ft_printf("bash: cd: OLDPWD not set\n"), NULL);
		ft_printf("%s\n", path);
	}
	else if (psplit[1][0] == '$')
		path = ft_cdexpandpath(psplit[1], envlist, varlist);
	else
		path = ft_copystring(psplit[1]);
	return (free_pointer(psplit), path);
}

char	**ft_handlecdsplit(char *str, char **var)
{
	char	**out;
	int		count;
	int		index;

	out = safe_dp_malloc(1);
	if (out == NULL)
		return (NULL);
	count = -1;
	index = -1;
	while (var[++count] != NULL)
	{
		if ((count > 0) && ((size_t)(ft_strstr(str, var[count]) \
			- ft_strstr(str, var[count - 1])) == ft_strlen(var[count - 1])))
			out[index] = ft_mergevarval(str, out[index], var[count]);
		else
		{
			index++;
			out = ft_realloc_dp(out, var[count], ft_strlen_dp(out) + 1);
		}
		if (count > 0)
			str = ft_strstr(str + ft_strlen(var[count - 1]), var[count]);
	}
	return (free_pointer(var), out);
}

char	*ft_cdexpandpath(char *pathstr, t_envlist **envlist, \
	t_varlist **varlist)
{
	char	*out;
	char	*varname;

	varname = pathstr++;
	if (!ft_checkvarname(varname))
		return (NULL);
	out = ft_getenv(varname, *envlist, *varlist);
	return (out);
}

char	*ft_copystring(char *str)
{
	char	*path;
	int		len;
	int		count;
	int		offset;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	path = (char *)malloc(sizeof(char) * (len + 1));
	ft_bzero(path, len + 1);
	if (!path)
		return (NULL);
	offset = 0;
	count = 0;
	while ((count + offset) < len)
	{
		if (str[count + offset] == '\"' || str[count + offset] == '\'')
			offset++;
		path[count] = str[count + offset];
		count++;
	}
	path[count] = '\0';
	return (path);
}
