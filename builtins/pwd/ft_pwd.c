/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:20:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/14 14:10:25 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	ft_pwd(char *str)
{
	char	currdir[PATH_MAX];

	(void)str;
	getcwd(currdir, sizeof(currdir));
	ft_printf("%s\n", currdir);
}
