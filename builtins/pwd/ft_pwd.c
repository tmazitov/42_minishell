/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:20:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/26 14:41:58 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_pwd()
{
	// char	*path;
	char	currdir[PATH_MAX];

	// path = getenv("PWD");
	getcwd(currdir, sizeof(currdir));
	// ft_printf("%s\n", path);
	ft_printf("%s\n", currdir);
}
