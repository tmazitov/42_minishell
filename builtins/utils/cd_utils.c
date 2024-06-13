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

int	ft_update_envlist(char *path, char *currdir, t_envlist **envlist)
{
	int		oldpwd_exist;
	char	*oldpwd_value;

	oldpwd_exist = 0;
	oldpwd_value = ft_copystring(currdir);
	while (*envlist != NULL)
	{
		if (ft_strncmp("PWD", (*envlist)->varname, \
			ft_strlen((*envlist)->varname)) == 0)
		{
			free((*envlist)->value);
			(*envlist)->value = path;
		}
		if (ft_strncmp("OLDPWD", (*envlist)->varname, \
			ft_strlen((*envlist)->varname)) == 0)
		{
			oldpwd_exist = 1;
			free((*envlist)->value);
			(*envlist)->value = oldpwd_value;
		}
		(*envlist) = (*envlist)->next;
	}
	if (oldpwd_exist == 0)
		(*envlist) = ft_create_env(NULL, "OLDPWD", oldpwd_value);
	return (1);
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
