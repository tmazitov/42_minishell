/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:07:42 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/25 22:34:19 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_cd(char *str) //UPDATE LOCAL ENV OLDPWD AND PWD
{
	char	**path_split;
	char	*path;

	path_split = ft_split(str, ' ');
	path = path_split[1];
	while ((path != NULL) && (*path != '\0') && ft_isspace(*path) > 0)
		path++;
	ft_printf("path raw: %s\n", path);
	if (path == NULL || *path == '\0')
		path = getenv("HOME");
	else if (*path == '-')
		path = getenv("OLDPWD");
	else if (ft_strncmp(path, "~", 1) == 0)
		path = getenv("HOME");
	ft_printf("path before chdir: %s\n", path);
	if (chdir(path) != 0)
	{
		ft_printf("bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	else
		ft_printf("changed directory\n");
	return (1);
}
