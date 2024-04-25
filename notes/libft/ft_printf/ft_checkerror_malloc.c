/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkerror_malloc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:54:30 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:23:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_checkerror_malloc(t_print *tab, char *error_malloc)
{
	if (!error_malloc)
	{
		tab->error = -1;
		return (-1);
	}
	return (1);
}
