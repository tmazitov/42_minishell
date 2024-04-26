/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:07:42 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/26 18:11:46 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_cd(char *str, t_envlist **envlist, t_varlist **varlist)
{
	char	currdir[PATH_MAX];
	char	*path;

	getcwd(currdir, sizeof(currdir));
	path = ft_getpath(str, *envlist, *varlist);
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

char	*ft_getpath(char *str, t_envlist *envlist, t_varlist *varlist)
{
	char	**path_split;
	char	*path;

	path = str;
	path_split = ft_split(str, ' ');
	if (path_split[1] == NULL || (*path_split[1] == '~' && \
		ft_strlen(path_split[1]) == 1))
		path = ft_getenv("HOME", envlist, varlist);
	else if (*path_split[1] == '~' && ft_strlen(path_split[1]) > 1)
		path = ft_expandhomepath(path_split, envlist, varlist);
	else if (*path_split[1] == '-' && ft_strlen(path_split[1]) == 1)
	{
		path = ft_getenv("OLDPWD", envlist, varlist);
		if (path == NULL)
		{
			ft_printf("bash: cd: OLDPWD not set\n");
			return (NULL);
		}
		ft_printf("%s\n", path);
	}
	else
		path = ft_getrawpath(path_split[1]);
	return (free_pointer(path_split), path);
}

char	*ft_getrawpath(char *str)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * ft_strlen(str));
	ft_strlcpy(path, str, ft_strlen(str) + 1);
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

int	ft_update_envlist(char *path, char *currdir, t_envlist **envlist)
{
	int		oldpwd_exist;
	char	*oldpwd_value;

	oldpwd_exist = 0;
	oldpwd_value = (char *)malloc(sizeof(char) * ft_strlen(currdir) + 1);
	if (!oldpwd_value)
		return (0);
	ft_strlcpy(oldpwd_value, currdir, ft_strlen(currdir) + 1);
	while (*envlist != NULL)
	{
		if (ft_strncmp("PWD", (*envlist)->varname, \
			ft_strlen((*envlist)->varname)) == 0)
			(*envlist)->value = path;
		if (ft_strncmp("OLDPWD", (*envlist)->varname, \
			ft_strlen((*envlist)->varname)) == 0)
		{
			oldpwd_exist = 1;
			(*envlist)->value = oldpwd_value;
		}
		(*envlist) = (*envlist)->next;
	}
	if (oldpwd_exist == 0)
		(*envlist) = ft_create_env("OLDPWD", currdir);
	return (1);
}
