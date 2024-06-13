/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:36:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/13 16:55:06 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*s1 != *s2)
			return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
		if (*s1 == '\0')
			break ;
		s1++;
		s2++;
		n--;
	}
	return (0);
}
