/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:30:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/21 22:55:48 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_free_env(t_envlist **envlist)
{
	t_envlist			*prev;

	while (*envlist != NULL)
	{
		free((*envlist)->value);
		free((*envlist)->varname);
		prev = *envlist;
		*envlist = (*envlist)->next;
		free(prev);
	}
}

int	cdcheck_path(char *path)
{
	int	exit_status;
	DIR	*dir;

	exit_status = 0;
	if (path == NULL)
		return (ft_err_b("bash: cd: OLDPWD not set\n", NULL, NULL), 1);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		chdir(path);
	}
	else if (EACCES == errno)
	{
		ft_err_b("bash: cd: ", path, ": Permission denied\n");
		return (1);
	}
	else if (ENOTDIR == errno)
	{
		ft_err_b("bash: cd: ", path, ": Not a directory\n");
		return (1);
	}
	else
		exit_status = ft_checkcderr(path);
	return (exit_status);
}

char	*ft_getpath_a(char **psplit, t_envlist **envlist, t_varlist **varlist)
{
	char	*path;

	if (psplit[1])
		psplit[1] = ft_cdcleanvalue(psplit[1]);
	if (psplit[1] == NULL || (*psplit[1] == '~' && ft_strlen(psplit[1]) == 1))
		path = ft_copystring(ft_getenv("HOME", *envlist, *varlist));
	else if (*psplit[1] == '~' && ft_strlen(psplit[1]) > 1)
		path = ft_expandhomepath(psplit, *envlist, *varlist);
	else if (psplit[1][0] == '$')
		path = ft_cdexpandpath(psplit[1], envlist, varlist);
	else if (*psplit[1] == '.' && ft_strlen(psplit[1]) == 1)
		path = ft_cddot(psplit[1]);
	else
		path = ft_copystring(psplit[1]);
	return (path);
}

char	*ft_cddot(char *path)
{
	char		currdir[PATH_MAX];

	getcwd(currdir, sizeof(currdir));
	path = ft_copystring(currdir);
	return (path);
}

int	ft_checkcderr(char *path)
{
	if (ENOENT == errno)
	{
		ft_err_b("bash: cd: ", path, ": No such file or directory\n");
		return (1);
	}
	else if (ENAMETOOLONG == errno)
	{
		ft_err_b("bash: cd: ", path, ": File name too long\n");
		return (1);
	}
	else if (EFAULT == errno)
	{
		ft_err_b("bash: cd: ", path, ": path inaccessbile\n");
		return (1);
	}
	else if (EIO == errno)
	{
		ft_err_b("bash: cd: ", path, ": I/O error occurred\n");
		return (1);
	}
	else
		return (0);
}

	// if (ft_strlen(path) > NAME_MAX)
	// {
	// 	ft_err_b("bash: cd: ", path, ": File name too long\n");
	// 	return (free(path), 1);
	// }
	// if (chdir(path) != 0)
	// {
	// 	ft_err_b("bash: cd: ", path, ": No such file or directory\n");
	// 	return (free(path), 1);
	// }