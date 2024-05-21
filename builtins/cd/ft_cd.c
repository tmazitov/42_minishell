/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:07:42 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/21 21:42:38 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_cd(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	currdir[PATH_MAX];
	char	*path;

	getcwd(currdir, sizeof(currdir));
	path = ft_getpath(str, envlist, varlist);
	if (path == NULL)
		return (0);
	if (chdir(path) != 0)
	{
		ft_printf("bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	ft_update_envlist(path, currdir, envlist);
	return (1);
}

char	*ft_getpath(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	**path_split;
	char	*path;

	path = str;
	path_split = ft_split(str, ' ');
	if (path_split[1] == NULL || (*path_split[1] == '~' && \
		ft_strlen(path_split[1]) == 1))
		path = ft_copystring(ft_getenv("HOME", *envlist, *varlist));
	else if (*path_split[1] == '~' && ft_strlen(path_split[1]) > 1)
		path = ft_expandhomepath(path_split, *envlist, *varlist);
	else if (*path_split[1] == '-' && ft_strlen(path_split[1]) == 1)
	{
		path = ft_copystring(ft_getenv("OLDPWD", *envlist, *varlist));
		if (path == NULL)
		{
			ft_printf("bash: cd: OLDPWD not set\n");
			return (NULL);
		}
		ft_printf("%s\n", path);
	}
	else if (path_split[1][0] == '$')
		path = ft_cdexpandpath(path_split[1], envlist, varlist);
	else
		path = ft_copystring(path_split[1]);
	return (free_pointer(path_split), path);
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

	len = ft_strlen(str);
	path = (char *)malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	count = 0;
	while (count < len)
	{
		path[count] = str[count];
		count++;
	}
	path[count] = '\0';
	return (path);
}

char	*ft_expandhomepath(char **path_split, t_envlist *envlist, \
	t_varlist *varlist)
{
	char	*path;
	char	*homepath;
	char	**newpath_split;
	size_t	tot_len;

	newpath_split = ft_split(path_split[1], '~');
	homepath = ft_getenv("HOME", envlist, varlist);
	tot_len = (ft_strlen(homepath) + ft_strlen(newpath_split[0]) + 1);
	path = (char *)malloc(sizeof(char) * tot_len);
	ft_memset(path, 0, tot_len);
	ft_strlcat(path, homepath, ft_strlen(homepath) + 1);
	ft_strlcat(path, newpath_split[0], ft_strlen(homepath) + \
		ft_strlen(newpath_split[0]) + 1);
	path[ft_strlen(homepath) + ft_strlen(newpath_split[0])] = '\0';
	free_pointer(newpath_split);
	return (path);
}
