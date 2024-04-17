/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:11:06 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:22:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	cmp = c;
	size_t		n;

	n = ft_strlen(s) + 1;
	while (n--)
	{
		if (*s == cmp)
			return ((char *)(s));
		if (!*s)
			return (NULL);
		s++;
	}
	return (NULL);
}

//const char cpm = char --> declare init value of cmp