/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writestring_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:27:51 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 21:28:13 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

void	ft_err_b(char *str1, char *str2, char *str3)
{
	if (str1)
		write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
}
