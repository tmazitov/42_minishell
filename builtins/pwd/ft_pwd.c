/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:20:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/05/19 18:00:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_pwd(char *str)
{
	char	**path_split;
	char	currdir[PATH_MAX];

	path_split = ft_split(str, ' ');
	if (ft_strlen_dp(path_split) > 1)
		ft_printf("pwd: too many arguments\n");
	else
	{
		// path = getenv("PWD");
		getcwd(currdir, sizeof(currdir));
		// ft_printf("%s\n", path);
		ft_printf("%s\n", currdir);
	}
	free_pointer(path_split);
}
