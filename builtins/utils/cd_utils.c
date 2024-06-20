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

int	ft_update_envlist(char *oldpwd_value, t_envlist **envlist)
{
	int			oldpwd_exist;
	char		cdir[PATH_MAX];
	t_envlist	*env_head;

	oldpwd_exist = 0;
	getcwd(cdir, sizeof(cdir));
	env_head = *envlist;
	while (*envlist != NULL)
	{
		if (ft_compname("PWD", (*envlist)->varname))
		{
			free((*envlist)->value);
			(*envlist)->value = ft_copystring(cdir);
		}
		if (ft_compname("OLDPWD", (*envlist)->varname))
		{
			oldpwd_exist = 1;
			free((*envlist)->value);
			(*envlist)->value = oldpwd_value;
		}
		(*envlist) = (*envlist)->next;
	}
	if (oldpwd_exist == 0)
		ft_setenvlist(ft_strdup("OLDPWD"), oldpwd_value, 1, &env_head);
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

char	*ft_cdcleanvalue(char *str)
{
	size_t	len;
	size_t	index;
	char	*out;
	char	*str_temp;

	str_temp = str;
	len = 0;
	while (ft_isspace(*str) > 0)
		str++;
	out = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!out)
		return (NULL);
	ft_bzero(out, ft_strlen(str) + 1);
	index = 0;
	while (str[len] != '\0' && str[len] != '\n')
	{
		if (str[len] != '\"' && str[len] != '\'')
			out[len - index] = str[len];
		else
			index++;
		len++;
	}
	out[len] = '\0';
	free(str_temp);
	return (out);
}

void	free_cd(char **str_split, char *path)
{
	if (str_split)
		free_pointer(str_split);
	if (path)
		free(path);
}

char	**cd_split(char *str)
{
	char	**psplit;

	if (str == NULL)
		return (NULL);
	psplit = ft_splittoken_setvar(str);
	psplit = str_token(psplit);
	psplit = ft_handlecdsplit(str, psplit);
	return (psplit);
}
