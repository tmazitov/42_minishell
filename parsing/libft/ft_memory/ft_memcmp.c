/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:23:24 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:23:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;

	if (len != 0)
		while (len--)
			if (*p1++ != *p2++)
				return (*--p1 - *--p2);
	return (0);
}
