/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:51:20 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:22:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		n;

	d = dst;
	s = src;
	n = dstsize;
	if (n != 0 && --n != 0)
	{
		while (n)
		{
			*d = *s++;
			if (!*d++)
				break ;
			n--;
		}
	}
	if (n == 0)
	{
		if (dstsize != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
