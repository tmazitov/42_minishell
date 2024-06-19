/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:07:42 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 18:04:59 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_cd(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char		currdir[PATH_MAX];
	char		*path;
	static int	pwd_stat;

	if (ft_checkvarenv("PWD", *envlist))
		pwd_stat = 0;
	if (str == NULL)
		return (0);
	if (!ft_checkvarenv("PWD", *envlist) && pwd_stat == 0)
	{
		pwd_stat = 1;
		currdir[0] = '\0';
	}
	else
		getcwd(currdir, sizeof(currdir));
	path = ft_getpath(str, envlist, varlist);
	if (cdcheck_path(path) == 1)
		return (1);
	ft_update_envlist(currdir, envlist);
	return (free(path), 0);
}

char	*ft_getpath(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	**psplit;
	char	*path;

	psplit = cd_split(str);
	if (psplit[1])
		psplit[1] = ft_cdcleanvalue(psplit[1]);
	if (psplit[1] == NULL || (*psplit[1] == '~' && ft_strlen(psplit[1]) == 1))
		path = ft_copystring(ft_getenv("HOME", *envlist, *varlist));
	else if (*psplit[1] == '~' && ft_strlen(psplit[1]) > 1)
		path = ft_expandhomepath(psplit, *envlist, *varlist);
	else if (*psplit[1] == '-' && ft_strlen(psplit[1]) == 1)
	{
		path = ft_copystring(ft_getenv("OLDPWD", *envlist, *varlist));
		if (!*path)
			return (free_cd(psplit, path), NULL);
		if (path == NULL)
			return (free_pointer(psplit), NULL);
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
