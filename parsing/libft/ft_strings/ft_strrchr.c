/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:22:17 by emaravil          #+#    #+#             */
/*   Updated: 2024/04/17 03:23:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *p, int ch)
{
	char	c;
	size_t	len;

	c = (char)ch;
	len = ft_strlen(p) + 1;
	while (len--)
		if (p[len] == c)
			return ((char *)&p[len]);
	return (NULL);
}
