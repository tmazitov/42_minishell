/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:24:43 by emaravil          #+#    #+#             */
/*   Updated: 2024/06/19 13:46:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*copy;

	if (!str)
		return (NULL);
	len = ft_strlen(str) + 1;
	copy = malloc(len);
	if (!(copy))
		return (NULL);
	ft_memcpy(copy, str, len);
	return (copy);
}
