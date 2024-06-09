/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:18:49 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:23:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;
	const char	*h_temp;

	if (!*needle)
		return ((char *)haystack);
	h = haystack;
	while (*h)
	{
		h_temp = h;
		n = needle;
		while (*h_temp && *n && *h_temp == *n)
		{
			h_temp++;
			n++;
		}
		if (!*n)
			return ((char *)h);
		h++;
	}
	return (NULL);
}
