/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:48:39 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:24:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *dst, int c, size_t length)
{
	unsigned char	*p;

	p = dst;
	while (length--)
		*p++ = c;
	return (dst);
}
