/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:23:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:23:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *src, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	cmp;

	cmp = (unsigned char)c;
	p = (unsigned char *)src;
	while (len--)
		if (*p++ == cmp)
			return ((char *)(--p));
	return (NULL);
}
