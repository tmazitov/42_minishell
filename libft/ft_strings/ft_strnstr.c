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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	slen;

	if (!*needle)
		return ((char *)haystack);
	if ((!haystack && !len) || !*haystack)
		return (NULL);
	slen = ft_strlen(needle);
	while (*haystack && len-- >= slen)
	{
		if (ft_strncmp(haystack++, needle, slen) == 0)
			return ((char *)--haystack);
	}
	return (NULL);
}
